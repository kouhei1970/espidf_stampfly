#include "sensors.h"

bool Sensors::initializeAllSensors() {
    bool result = true;
    
    result &= attitude.initialize();
    result &= compass.initialize();
    result &= barometer.initialize();
    result &= distance.initialize();
    result &= opticalFlow.initialize();
    result &= powerMonitor.initialize();
    
    return result;
}

bool Sensors::configureAllSensors() {
    bool result = true;
    
    result &= attitude.configure();
    result &= compass.configure();
    result &= barometer.configure();
    result &= distance.configure();
    result &= opticalFlow.configure();
    result &= powerMonitor.configure();
    
    return result;
}

bool Sensors::checkAllSensorStatus() {
    bool result = true;
    
    result &= attitude.checkStatus();
    result &= compass.checkStatus();
    result &= barometer.checkStatus();
    result &= distance.checkStatus();
    result &= opticalFlow.checkStatus();
    result &= powerMonitor.checkStatus();
    
    return result;
}

bool Sensors::resetAllSensors() {
    bool result = true;
    
    result &= attitude.reset();
    result &= compass.reset();
    result &= barometer.reset();
    result &= distance.reset();
    result &= opticalFlow.reset();
    result &= powerMonitor.reset();
    
    return result;
}
