<<<<<<< HEAD
#include "hayai-stopwatch.hpp"
#include <cstddef>
#include <sys/time.h>
#include <stdint.h>
#include <auto_ptr.h>
=======
#include <cstddef>
#include <sys/time.h>
#include <stdint.h>
>>>>>>> ce710f7... Initial commit.

#ifndef __HAYAI_TEST
#define __HAYAI_TEST
namespace Hayai
{
<<<<<<< HEAD
    enum CLOCK_TIME {
        NORM = 0,
        REALTIME = 1
    };

    class TestStopWatchHelper : public  StopWatchMetricCollector {
        public:
        timespec d_difftime;
        virtual void collecttime (const timespec& difftime) {
            d_difftime.tv_sec = difftime.tv_sec;
            d_difftime.tv_nsec = difftime.tv_nsec;
        }
    };

=======
>>>>>>> ce710f7... Initial commit.
    /// Base test class.
    
    /// @ref SetUp is invoked before each run, and @ref TearDown is invoked 
    /// once the run is finished. Iterations rely on the same fixture 
    /// for every run.
    /// 
    /// The default test class does not contain any actual code in the 
    /// SetUp and TearDown methods, which means that tests can inherit 
    /// this class directly for non-fixture based benchmarking tests.
    class Test
    {
    public:
        /// Set up the testing fixture for execution of a run.
        virtual void SetUp()
        {
            
        }
        
        
        /// Tear down the previously set up testing fixture after the 
        /// execution run.
        virtual void TearDown()
        {
            
        }
        
        
        /// Run the test.
        
        /// @param iterations Number of iterations to gather data for.
        /// @returns the number of microseconds the run took.
<<<<<<< HEAD
        int64_t Run(std::size_t iterations, CLOCK_TIME clockTime = NORM)
=======
        int64_t Run(std::size_t iterations)
>>>>>>> ce710f7... Initial commit.
        {
            // Set up the testing fixture.
            this->SetUp();
            
<<<<<<< HEAD
            if (clockTime = NORM) {
                // Get the starting time.
                struct timeval startTime,
                               endTime;

                gettimeofday(&startTime,
                        NULL);

                // Run the test body for each iteration.
                std::size_t iteration = iterations;
                while (iteration--)
                    this->TestBody();

                // Get the ending time.
                gettimeofday(&endTime,
                        NULL);

                // Tear down the testing fixture.
                this->TearDown();

                // Return the duration in microseconds.
                return (endTime.tv_sec - startTime.tv_sec) * 1000000 + 
                    (endTime.tv_usec - startTime.tv_usec);
            } else {
                TestStopWatchHelper helper;
                {
                    StopWatchGuard(std::auto_ptr<StopWatch>(new StopWatch(&helper)));

                    // Run the test body for each iteration.
                    std::size_t iteration = iterations;
                    while (iteration--)
                        this->TestBody();

                }
                return helper.d_difftime.tv_sec * 1000000000 + helper.d_difftime.tv_nsec;
            }
=======
            // Get the starting time.
            struct timeval startTime,
                           endTime;
            
            gettimeofday(&startTime,
                         NULL);
            
            // Run the test body for each iteration.
            std::size_t iteration = iterations;
            while (iteration--)
                this->TestBody();
            
            // Get the ending time.
            gettimeofday(&endTime,
                         NULL);
            
            // Tear down the testing fixture.
            this->TearDown();
            
            // Return the duration in microseconds.
            return (endTime.tv_sec - startTime.tv_sec) * 1000000 + 
                   (endTime.tv_usec - startTime.tv_usec);
>>>>>>> ce710f7... Initial commit.
        }
    protected:
        /// Test body.
        
        /// Executed for each iteration the benchmarking test is run.
        virtual void TestBody()
        {
            
        }
    };
}
#endif
