#ifndef DEFINED_HAYAI_STOPWATCH_H
#define DEFINED_HAYAI_STOPWATCH_H

#include <time.h>
#include <errno.h>
#include <auto_ptr.h>
#include <stdexcept>
#include <sstream>

namespace Hayai { 

    /**
     * @desc This class represents a Stop watch metric collector to whom a given stop
     *       watch instance would report times to. As of now the cardinality of the 
     *       relationship between these classes is 1:1
     */
    class StopWatchMetricCollector {
        public:
            /**
             * @desc This method collects and processes the recieved timespec structure
             *       Any state is only held by the class implementing this method not
             *       the caller.
             */
            virtual void collecttime(const struct timespec&) = 0;
            virtual ~StopWatchMetricCollector(){}
    };

    /**
     * @desc This class represents a stop watch instance. It is based on the realtime
     *       clock and depends on the system conforming to POSIX and having <time.h>
     *       This is mainly to be used for debugging/profiling purposes. Quantify/Gprof
     *       is great for getting the breakdowns of existing programs and drilling down
     *       on the details. This is intended more as a test fixture for prototyping or
     *       testing code.
     *       This class is a non-copyable class.
     *       
     */
    class StopWatch {
        private:
        timespec d_initTime;
        timespec d_resTime;
        /// Metric collector. Optional. Held not owned.
        StopWatchMetricCollector* d_metricCollector;
        public:
        StopWatch(StopWatchMetricCollector* metricCollector) : 
            d_metricCollector(metricCollector) {
            int rc = clock_getres(CLOCK_REALTIME,&d_resTime);
            rc = clock_gettime(CLOCK_REALTIME,&d_initTime);
            if (rc != 0) {
                int errNumber = errno;
                std::ostringstream errStr;
                errStr << errNumber;
                throw std::runtime_error(errStr.str());
            }
        };

        void report() {
            timespec curTime,result;
            clock_gettime(CLOCK_REALTIME,&curTime);
            if (d_initTime.tv_nsec < curTime.tv_nsec) {
                int nsec = (curTime.tv_nsec - d_initTime.tv_nsec) / 1000000 + 1;
                curTime.tv_nsec -= 1000000 * nsec;
                curTime.tv_sec += nsec;
            }
            if (d_initTime.tv_nsec - curTime.tv_nsec > 1000000) {
                int nsec = (d_initTime.tv_nsec - curTime.tv_nsec) / 1000000;
                curTime.tv_nsec += 1000000 * nsec;
                curTime.tv_sec -= nsec;
            }

            result.tv_sec = d_initTime.tv_sec - curTime.tv_sec;
            result.tv_nsec = d_initTime.tv_nsec - curTime.tv_nsec;
            d_metricCollector->collecttime(result);
        }
    };
    
    class StopWatchGuard {
        private:
            std::auto_ptr<StopWatch> d_stopwatch;

        public:
            /**
             * @desc This constructs a stop watch guard object. It holds and owns a stop
             *       watch object that will be released as the destructor for the class
             *       is called.
             */
            StopWatchGuard(std::auto_ptr<StopWatch> stopwatch) : d_stopwatch(stopwatch) {
            };

            /**
             * @desc This is the destructor of the class. It calls the report method that 
             * triggers a collection of the time metric of the owned stop watch instance.
             */
            ~StopWatchGuard() {
                d_stopwatch->report();
            }
    };

}

#endif //DEFINED_HAYAI_STOPWATCH_H
