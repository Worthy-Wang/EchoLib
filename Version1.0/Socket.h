#pragma once

namespace wd
{
    class Socket
    {
    public:
        Socket();
        explicit
        Socket(int fd);
        ~Socket();
        int getFd() const;
        void shutdown_write();
    private:
        int _fd;
    };
} // namespace wd