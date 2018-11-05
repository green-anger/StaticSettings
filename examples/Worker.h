#pragma once

#include <memory>
#include <thread>


class Worker
{
public:
    Worker();
    ~Worker();
    Worker( Worker&& ) = default;

private:
    static int uid_;
    const int id_;

    std::unique_ptr<std::thread> t_;
};
