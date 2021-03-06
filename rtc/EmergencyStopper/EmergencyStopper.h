// -*- C++ -*-
/*!
 * @file  EmergencyStopper.h
 * @brief emergency stopper
 * @date  $Date$
 *
 * $Id$
 */

#ifndef EMERGENCY_STOPPER_H
#define EMERGENCY_STOPPER_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <hrpModel/Body.h>
#include "interpolator.h"
#include "HRPDataTypes.hh"
#include <queue>

// Service implementation headers
// <rtc-template block="service_impl_h">
#include "EmergencyStopperService_impl.h"

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;

/**
   \brief sample RT component which has one data input port and one data output port
*/
class EmergencyStopper
    : public RTC::DataFlowComponentBase
{
public:
    /**
       \brief Constructor
       \param manager pointer to the Manager
    */
    EmergencyStopper(RTC::Manager* manager);
    /**
       \brief Destructor
    */
    virtual ~EmergencyStopper();

    // The initialize action (on CREATED->ALIVE transition)
    // formaer rtc_init_entry()
    virtual RTC::ReturnCode_t onInitialize();

    // The finalize action (on ALIVE->END transition)
    // formaer rtc_exiting_entry()
    virtual RTC::ReturnCode_t onFinalize();

    // The startup action when ExecutionContext startup
    // former rtc_starting_entry()
    // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

    // The shutdown action when ExecutionContext stop
    // former rtc_stopping_entry()
    // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

    // The activated action (Active state entry action)
    // former rtc_active_entry()
    virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

    // The deactivated action (Active state exit action)
    // former rtc_active_exit()
    virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

    // The execution action that is invoked periodically
    // former rtc_active_do()
    virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

    // The aborting action when main logic error occurred.
    // former rtc_aborting_entry()
    // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

    // The error action in ERROR state
    // former rtc_error_do()
    // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

    // The reset action that is invoked resetting
    // This is same but different the former rtc_init_entry()
    // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);

    // The state update action that is invoked after onExecute() action
    // no corresponding operation exists in OpenRTm-aist-0.2.0
    // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

    // The action that is invoked when execution context's rate is changed
    // no corresponding operation exists in OpenRTm-aist-0.2.0
    // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);
    bool stopMotion();
    bool releaseMotion();
    bool getEmergencyStopperParam(OpenHRP::EmergencyStopperService::EmergencyStopperParam& i_param);
    bool setEmergencyStopperParam(const OpenHRP::EmergencyStopperService::EmergencyStopperParam& i_param);

protected:
    // Configuration variable declaration
    // <rtc-template block="config_declare">
  
    // </rtc-template>

    TimedDoubleSeq m_qRef;
    TimedDoubleSeq m_q;
    TimedLong m_emergencySignal;
    TimedLong m_emergencyMode;
    OpenHRP::TimedLongSeqSeq m_servoState;

    // DataInPort declaration
    // <rtc-template block="inport_declare">
    InPort<TimedDoubleSeq> m_qRefIn;
    InPort<TimedLong> m_emergencySignalIn;
    InPort<OpenHRP::TimedLongSeqSeq> m_servoStateIn;
  
    // </rtc-template>

    // DataOutPort declaration
    // <rtc-template block="outport_declare">
    OutPort<TimedDoubleSeq> m_qOut;
    OutPort<TimedLong> m_emergencyModeOut;
  
    // </rtc-template>

    // CORBA Port declaration
    // <rtc-template block="corbaport_declare">
  
    // </rtc-template>

    // Service declaration
    // <rtc-template block="service_declare">
    RTC::CorbaPort m_EmergencyStopperServicePort;
  
    // </rtc-template>

    // Consumer declaration
    // <rtc-template block="consumer_declare">
    EmergencyStopperService_impl m_service0;
  
    // </rtc-template>

private:
    hrp::BodyPtr m_robot;
    double m_dt;
    unsigned int m_debugLevel;
    int dummy, loop;
    bool is_stop_mode, prev_is_stop_mode;
    bool is_initialized;
    int recover_time, retrieve_time;
    double recover_time_dt;
    int default_recover_time, default_retrieve_time;
    double *m_stop_posture;
    interpolator* m_interpolator;
    std::queue<std::vector<double> > m_input_posture_queue;
    int emergency_stopper_beep_count, emergency_stopper_beep_freq;
    coil::Mutex m_mutex;
};


extern "C"
{
    void EmergencyStopperInit(RTC::Manager* manager);
};

#endif // EMERGENCY_STOPPER_H
