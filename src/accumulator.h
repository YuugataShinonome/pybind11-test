#pragma once

#include <vector>
#include <unistd.h>
#include <pthread.h>
#include <iostream>

static int get_recommended_thread_count_() {
    int num_cpus = sysconf(_SC_NPROCESSORS_ONLN);
    if (num_cpus < 1) {
        num_cpus = 1;
    }
    return num_cpus;
}

template<typename T>
struct ThreadData
{
    const T *arr;
    T *result;
    int n;
    int start;
};


template<typename T>
static void *accumulate_single_(void *thread_arg)
{
    T t{};
    auto *thread_data = static_cast<ThreadData<T>*>(thread_arg);
    for (int i = 0;i < thread_data->n; i++)
    {
        t += thread_data->arr[thread_data->start + i];
    }
    (*thread_data->result) = t;
    return nullptr;
}

// Accumulate array
template<typename T>
T accumulate(const std::vector<T> &arr, int n_threads)
{
    if (n_threads < 0)
    {
        n_threads = get_recommended_thread_count_();
    }
    int step = arr.size() / n_threads;
    int left = step * n_threads;
    auto *t = new T[n_threads]{};
    auto *thread_id = new pthread_t[n_threads]{};
    auto *thread_data = new ThreadData<T>*[n_threads]{};
    for (int i = 0;i < n_threads;i++)
    {
        auto arg = new ThreadData<T>{};
        arg->arr = &arr[0];
        arg->start = i * step;
        arg->n = step;
        arg->result = &t[i];
        thread_data[i] = arg;
        pthread_create(&thread_id[i], nullptr, &accumulate_single_<T>, arg);
    }
    T result{};
    for (int i = 0;i < n_threads;i++)
    {
        pthread_join(thread_id[i], nullptr);
        result += t[i];
        delete thread_data[i];
    }
    delete[] t, thread_id, thread_data;
    for (int i = left; i < arr.size(); i++)
    {
        result += arr[i];
    }
    return result;
}