package com.tns;

import android.os.Handler;

/**
 * Created by plamen5kov on 8/30/16.
 */
public class DynamicConfiguration {
    private Integer workerId;
    private ThreadScheduler threadScheduler;
    private Handler mainThreadhandler;

    public DynamicConfiguration(Integer workerId, ThreadScheduler threadScheduler) {
        this.workerId = workerId;
        this.threadScheduler = threadScheduler;
    }

    public DynamicConfiguration(Integer workerId, ThreadScheduler threadScheduler, Handler mainThreadhandler) {
        this(workerId, threadScheduler);
        this.mainThreadhandler = mainThreadhandler;
    }

    public Integer getWorkerId() {
        return workerId;
    }

    public ThreadScheduler getHandler() {
        return threadScheduler;
    }

    public Handler getMainThreadhandler() {
        return mainThreadhandler;
    }
}
