The program implements Publish Subscribe Sync Async service
Producers synchronously produce data.
Consumers asynchronously read the data.
All producers store the produced data in a FIFO queue buffer.
Each consumer runs in own thread and reads data from the FIFO.