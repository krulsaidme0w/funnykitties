namespace network {
    template <class T>
    class Tsqueue
    {
    private:
    public:
        Tsqueue();
        ~Tsqueue();

        const T& front() {
        }

        const T& back() {
        }

        T pop_front() {
        }

        T pop_back() {
        }

        void push_back(const T& item) {
        }

        void push_front(const T& item) {
        }

        bool empty() {
        }

        size_t count() {
        }

        void clear() {
        }

        void wait() {
        }

    protected:
        std::mutex muxQueue;
        std::deque<T> deqQueue;
        std::condition_variable cvBlocking;
        std::mutex muxBlocking;
    };
  
} // namespace network
