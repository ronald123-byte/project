#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <chrono>

// Job structure to hold job details
struct Job {
    int jobID;          // Unique identifier for the job
    int executionTime;  // Time to complete the job (in seconds)
    int priority;       // Higher priority jobs are executed first

    // Constructor for a Job
    Job(int id, int execTime, int pri) 
        : jobID(id), executionTime(execTime), priority(pri) {}
};

// Custom comparator for priority queue to sort by priority (highest first)
struct ComparePriority {
    bool operator()(const Job& a, const Job& b) {
        return a.priority < b.priority; // Higher priority jobs come first
    }
};

class JobScheduler {
private:
    std::priority_queue<Job, std::vector<Job>, ComparePriority> jobQueue; // Priority queue for jobs

public:
    // Add a job to the scheduler
    void addJob(int jobID, int executionTime, int priority) {
        Job newJob(jobID, executionTime, priority);
        jobQueue.push(newJob);
        std::cout << "Job " << jobID << " added to the queue with priority " << priority << " and execution time " << executionTime << " seconds.\n";
    }

    // Execute jobs based on priority
    void executeJobs() {
        while (!jobQueue.empty()) {
            Job currentJob = jobQueue.top();
            jobQueue.pop();
            std::cout << "Executing Job " << currentJob.jobID << " with priority " << currentJob.priority << "...\n";
            std::this_thread::sleep_for(std::chrono::seconds(currentJob.executionTime)); // Simulate execution time
            std::cout << "Job " << currentJob.jobID << " completed.\n";
        }
        std::cout << "All jobs have been executed.\n";
    }
};

int main() {
    // Create the scheduler instance
    JobScheduler scheduler;
    
    // Add jobs to the scheduler (jobID, executionTime, priority)
    scheduler.addJob(1, 2, 3);  // Job 1: Execution time = 2s, Priority = 3
    scheduler.addJob(2, 1, 1);  // Job 2: Execution time = 1s, Priority = 1
    scheduler.addJob(3, 3, 2);  // Job 3: Execution time = 3s, Priority = 2
    scheduler.addJob(4, 2, 5);  // Job 4: Execution time = 2s, Priority = 5 (highest priority)
    
    // Execute the jobs
    scheduler.executeJobs();
    
    return 0;
}
