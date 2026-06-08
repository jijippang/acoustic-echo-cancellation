
#include <vector>

#include "Eigen/Dense"



namespace sliding_window
{


template <typename T = double>
class SlidingWindow
{
    public:
        explicit SlidingWindow(std::size_t capacity) : buffer_(capacity), capacity_{capacity} {};
        explicit SlidingWindow(std::size_t capacity, const T& value) : buffer_(capacity), capacity_{capacity} { fill(value); };


        void fill(const T& value)
        {
            if (capacity_ == 0) { return; }

            const auto old_capacity = capacity_;
            reset();
            capacity_ = old_capacity;
            buffer_.assign(capacity_, value);
            size_ = capacity_;
        }

        void reset()
        {
            capacity_ = 0;
            size_ = 0;
            head_ = 0;
            tail_ = 0;

            // Reset the vector's size and capacity
            buffer_.clear();
            buffer_.shrink_to_fit();
            view_buffer_.clear();
            view_buffer_.shrink_to_fit();
        }

        void push(const T& element)
        {
            if (capacity_ == 0)
            {
                // Increase the capacity to the default capacity
                capacity_ = 1;
                buffer_.resize(capacity_);
            }

            // Insert element into the buffer at the head pointer
            buffer_[head_] = element;

            // Increment the head pointer to point to the next index
            head_ = (head_ + 1) % capacity_;

            if (size_ < capacity_)
            {
                // Increment the size if we haven't reached the full capacity yet
                size_++;
            }
            else if (size_ == capacity_)
            {
                // Increment the tail pointer if we have reached the full capacity
                tail_ = (tail_ + 1) % capacity_;
            }
        }

        T pop()
        {
            if (size_ == 0)
            {
                throw std::runtime_error("Cannot pop from an empty window");
            }

            // Retrieve the oldest element to remove since the buffer is a FIFO
            const T removed_elem = buffer_[tail_];

            // Increment the tail since the oldest element after popping is the next element after the current tail
            tail_ = (tail_ + 1) % capacity_;

            // Decrement the size since we removed an element
            size_--;

            return removed_elem;
        }

        std::size_t capacity() const { return capacity_; }
        std::size_t size() const { return size_; }
        bool empty() const { return size_ == 0; }
        const T& front() const { return buffer_[tail_]; }
        const T& back() const { return buffer_[(head_ - 1 + capacity_) % capacity_]; }

        Eigen::Map<Eigen::VectorXd> get_eigen_view()
        {
            if (size_ == 0)
            {
                throw std::runtime_error("Cannot get a view of an empty window");
            }

            if (tail_ + size_ <= capacity_)
            {
                // The buffer has not wrapped around
                return Eigen::Map<Eigen::VectorXd>(buffer_.data() + tail_, size_);
            }
            else
            {
                // The buffer has wrapped around
                view_buffer_.resize(size_);
                for (std::size_t i = 0; i < size_; ++i)
                {
                    view_buffer_[i] = buffer_[(tail_ + i) % capacity_];
                }
                return Eigen::Map<Eigen::VectorXd>(view_buffer_.data(), size_);
            }
        }

        Eigen::Map<const Eigen::VectorXd> get_eigen_view() const
        {
            if (size_ == 0)
            {
                throw std::runtime_error("Cannot get a view of an empty window");
            }

            if (tail_ + size_ <= capacity_)
            {
                // The buffer has not wrapped around
                return Eigen::Map<const Eigen::VectorXd>(buffer_.data() + tail_, size_);
            }
            else
            {
                // The buffer has wrapped around
                view_buffer_.resize(size_);
                for (std::size_t i = 0; i < size_; ++i)
                {
                    view_buffer_[i] = buffer_[(tail_ + i) % capacity_];
                }
                return Eigen::Map<const Eigen::VectorXd>(view_buffer_.data(), size_);
            }
        }

        Eigen::VectorXd get_eigen_copy() const
        {
            return Eigen::VectorXd(get_eigen_view());
        }


    private:
        // A FIFO circular buffer that holds the elements
        std::vector<T> buffer_;

        // A temporary buffer for views to hold contiguous elements if the buffer has wrapped around
        std::vector<T> view_buffer_;

        // The maximum size of the circular buffer
        std::size_t capacity_{};

        // Keeps track of the current size of the buffer
        std::size_t size_{};

        // Points to the next index to write to
        std::size_t head_{};

        // Points to the oldest element
        std::size_t tail_{};
};


} // namespace sliding_window




