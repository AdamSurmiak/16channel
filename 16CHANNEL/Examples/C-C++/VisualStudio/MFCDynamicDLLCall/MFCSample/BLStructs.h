
#pragma once

#ifndef _BLSTRUCTS_H_
#define _BLSTRUCTS_H_

#include <windows.h>
#include <WinDef.h>

/*
 * Bio-Logic Header file for ECLib C/C++ interface
 */

/**
 * \defgroup structures Structures and constants
 * @{
 */

#pragma pack(4) // needed because default pack size is 8, which produces an offset for some structures

/**
 * This structure holds information about the device that \ref BL_Connect connected to.
 */
typedef struct {
    INT32 DeviceCode;       /*!<  Device code see \ref TDeviceType_e */
    INT32 RAMSize;          /*!<  RAM size in MB */
    INT32 CPU;              /*!<  CPU type */
    INT32 NumberOfChannels; /*!<  Number of channels connected */
    INT32 NumberOfSlots;    /*!<  Number of slots available */
    INT32 FirmwareVersion;  /*!<  Communication firmware version */
    INT32 FirmwareDate_yyyy;/*!<  Communication firmware date YYYY */
    INT32 FirmwareDate_mm;  /*!<  Communication firmware date MM */
    INT32 FirmwareDate_dd;  /*!<  Communication firmware date DD */
    INT32 HTdisplayOn;      /*!<  Allow hyper-terminal prints (true/false) */
    INT32 NbOfConnectedPC;  /*!<  Number of connected PCs */
} TDeviceInfos_t;

/**
 * This structure holds information about the channel. You can obtain them using \ref BL_GetChannelInfos
 */
typedef struct {
    INT32 Channel;          /*!<  Channel (0..15) */
    INT32 BoardVersion;     /*!<  Board version */
    INT32 BoardSerialNumber;/*!<  Board serial number */
    INT32 FirmwareCode;     /*!<  Firmware loaded (see \ref TFirmwareCode_e) */
    INT32 FirmwareVersion;  /*!<  Firmware version */
    INT32 XilinxVersion;    /*!<  Xilinx version */
    INT32 AmpCode;          /*!<  Amplifier code (see \ref TAmplifierType_e) */
    INT32 NbAmps;           /*!<  Number of amplifiers */
    INT32 Lcboard;          /*!<  Low current board present (true/false) */
    INT32 Zboard;           /*!<  true if the channel has impedance measurement capability */
    INT32 RESERVED;         /*!<  not used */
    INT32 RESERVED2;        /*!<  not used */
    INT32 MemSize;          /*!<  Memory size (in bytes) */
    INT32 MemFilled;        /*!<  Memory filled (in bytes) */
    INT32 State;            /*!<  Channel State (see \ref TChannelState_e) */
    INT32 MaxIRange;        /*!<  Maximum I range allowed (see \ref TIntensityRange_e) */
    INT32 MinIRange;        /*!<  Minimum I range allowed (see \ref TIntensityRange_e) */
    INT32 MaxBandwidth;     /*!<  Maximum bandwidth allowed (see \ref TBandwidth_e) */
    INT32 NbOfTechniques;   /*!<  Number of techniques loaded */
} TChannelInfos_t;

/**
 * This structure contains information about the channel current values measurement.
 */
typedef struct { 
    INT32 State;        /*!<  Channel state: see \ref TChannelState_e. */
    INT32 MemFilled;    /*!<  Memory filled (in Bytes) */
    FLOAT TimeBase;     /*!<  Time base (s) */
    FLOAT Ewe;          /*!<  Working electrode potential (V) */
    FLOAT EweRangeMin;  /*!<  Ewe min range (V) */
    FLOAT EweRangeMax;  /*!<  Ewe max range (V) */
    FLOAT Ece;          /*!<  Counter electrode potential (V) */
    FLOAT EceRangeMin;  /*!<  Ece min range (V) */
    FLOAT EceRangeMax;  /*!<  Ece max range (V) */
    INT32 Eoverflow;    /*!<  Potential overflow */
    FLOAT I;            /*!<  Current value (A) */
    INT32 IRange;       /*!<  Current range (see \ref TIntensityRange_e) */
    INT32 Ioverflow;    /*!<  Current overflow */
    FLOAT ElapsedTime;  /*!<  Elapsed time (s) */
    FLOAT Freq;         /*!<  Frequency (Hz) */
    FLOAT Rcomp;        /*!<  R compensation (Ohm) */
    INT32 Saturation;   /*!<  E or/and I saturation */
    INT32 OptErr;       /*!<  Hardware option error code (see \ref TErrorCodes_e, SP-300 series only) */
    INT32 OptPos;       /*!<  Index of the option generating the OptErr (SP-300 series only) */
} TCurrentValues_t;

/**
 * This structure holds metadata about the data you just received with \ref BL_GetData
 */
typedef struct {
    INT32  IRQskipped;      /*!<  Number of IRQ skipped */
    INT32  NbRows;          /*!<  Number of rows into the data buffer, i.e.number of points saved in the data buffer */
    INT32  NbCols;          /*!<  Number of columns into the data buffer, i.e. number of variables defining a point in the data buffer */
    INT32  TechniqueIndex;  /*!<  Index (0-based) of the technique who has generated the data. This field is only useful for linked techniques */
    INT32  TechniqueID;     /*!<  Identifier of the technique who has generated the data. Must be used to identify the data format into the data buffer (see \ref TTechniqueIdentifier_e ) */
    INT32  ProcessIndex;    /*!<  Index (0-based) of the process of the technique who has generated the data. Must be used to identify the data format into the data buffer */
    INT32  loop;            /*!<  Loop number */
    DOUBLE StartTime;       /*!<  Start time (s) */
    INT32  MuxPad;          /*!<  Active MP-MEA option pad number (SP-300 series only) */
} TDataInfos_t;


/**
 * This structure is used to retrieve data from the device by the function \ref BL_GetData
 */
typedef struct {
    UINT32 data[1000]; /*!< Buffer of size 1000 * 4 bytes */
} TDataBuffer_t;

/**
 * The structure \ref TEccParam_t defines an elementary technique parameter and is used by
 * the function \ref BL_LoadTechnique
 */
typedef struct {
    BYTE   ParamStr[64];/*!< string who defines the parameter label (see section 7. Techniques in PDF for a complete description of parameters available for each technique) */
    INT32  ParamType;   /*!<  Parameter type (see \ref TParamType_e) */
    INT32  ParamVal;    /*!<  Parameter value. \warning Numerical value */
    INT32  ParamIndex;  /*!<  Parameter index (0-based), useful for multi-step parameters. Otherwise should be 0. */
} TEccParam_t;

/**
 * The structure \ref TEccParams_t defines an array of elementary technique parameters and is used by the function \ref BL_LoadTechnique
 */
typedef struct {
    INT32        len;       /*!<  Length of the array pointed by pParams */
    TEccParam_t* pParams;   /*!<  Pointer on the array of technique parameters (array of structure \ref TEccParam_t) */
} TEccParams_t;

/** The structure \ref THardwareConf_t describes the channel electrode configuration. See \ref BL_GetHardConf and \ref BL_SetHardConf */
typedef struct {
    INT32 Conn;     /*!<  Electrode connection (see \ref TElectrodeConn_e) */
    INT32 Ground;   /*!<  Instrument ground (see \ref TElectrodeMode_e) */
} THardwareConf_t;

/** Technique informations */
typedef struct {
    INT32        id;            /*!< technique id */
    INT32        indx;          /*!< index of the technique */
    INT32        nbParams;      /*!< number of parameters */
    INT32        nbSettings;    /*!< number of hardware settings */
    TEccParam_t* Params;        /*!< pointer to the parameters */
    TEccParam_t* HardSettings;  /*!< pointer to the hardware settings */
} TTechniqueInfos;

/** Experiment informations */
typedef struct {
    INT32  Group;           /*!< TODO */
    INT32  PCidentifier;    /*!< TODO */
    INT32  TimeHMS;         /*!< TODO */
    INT32  TimeYMD;         /*!< TODO */
    BYTE   Filename[256];   /*!< TODO */
} TExperimentInfos_t;

/** This enum is used in \ref BL_Connect and \ref TDeviceInfos_t */
typedef enum {
    KBIO_DEV_VMP     = 0,   /*!<  VMP device */
    KBIO_DEV_VMP2    = 1,   /*!<  VMP2 device */
    KBIO_DEV_MPG     = 2,   /*!<  MPG device */
    KBIO_DEV_BISTAT  = 3,   /*!<  BISTAT device */
    KBIO_DEV_MCS200  = 4,   /*!<  MCS-200 device */
    KBIO_DEV_VMP3    = 5,   /*!<  VMP3 device */
    KBIO_DEV_VSP     = 6,   /*!<  VSP */
    KBIO_DEV_HCP803  = 7,   /*!<  HCP-803 */
    KBIO_DEV_EPP400  = 8,   /*!<  EPP-400 */
    KBIO_DEV_EPP4000 = 9,   /*!<  EPP-4000 */
    KBIO_DEV_BISTAT2 = 10,  /*!<  BISTAT 2 */
    KBIO_DEV_FCT150S = 11,  /*!<  FCT-150S */
    KBIO_DEV_VMP300  = 12,  /*!<  VMP-300 */
    KBIO_DEV_SP50    = 13,  /*!<  SP-50 */
    KBIO_DEV_SP150   = 14,  /*!<  SP-150 */
    KBIO_DEV_FCT50S  = 15,  /*!<  FCT-50S */
    KBIO_DEV_SP300   = 16,  /*!<  SP300 */
    KBIO_DEV_CLB500  = 17,  /*!<  CLB-500 */
    KBIO_DEV_HCP1005 = 18,  /*!<  HCP-1005 */
    KBIO_DEV_CLB2000 = 19,  /*!<  CLB-2000 */
    KBIO_DEV_VSP300  = 20,  /*!<  VSP-300 */
    KBIO_DEV_SP200   = 21,  /*!<  SP-200 */
    KBIO_DEV_MPG2    = 22,  /*!<  MPG2 */
    KBIO_DEV_SP100   = 23,  /*!<  SP-100 */
    KBIO_DEV_MOSLED  = 24,  /*!<  MOSLED */
    KBIO_DEV_KINEXXX = 25,  /*!<  Kinetic device... \warning unused code */
    KBIO_DEV_NIKITA  = 26,  /*!<  Nikita */
    KBIO_DEV_SP240   = 27,  /*!<  SP-240 */
    KBIO_DEV_MPG205  = 28,  /*!<  MPG-205 (techno VMP3) \warning not controled by kernel2 */
    KBIO_DEV_MPG210  = 29,  /*!<  MPG-210 (techno VMP3) \warning not controled by kernel2 */
    KBIO_DEV_MPG220  = 30,  /*!<  MPG-220 (techno VMP3) \warning not controled by kernel2 */
    KBIO_DEV_MPG240  = 31,  /*!<  MPG-240 (techno VMP3) \warning not controled by kernel2 */

    KBIO_DEV_UNKNOWN = 255  /*!<  Unknown device */
} TDeviceType_e;

/** Firmware codes */
typedef enum {
    KIBIO_FIRM_NONE    = 0, /*!<  No firmware loaded */
    KIBIO_FIRM_INTERPR = 1, /*!<  Firmware for EC-Lab software */
    KIBIO_FIRM_UNKNOWN = 4, /*!<  Unknown firmware loaded */
    KIBIO_FIRM_KERNEL  = 5, /*!<  Firmware for the library */
    KIBIO_FIRM_INVALID = 8, /*!<  Invalid firmware loaded */
    KIBIO_FIRM_ECAL    = 10 /*!<  Firmware for calibration software */
} TFirmwareCode_e;

/** Amplifier types */
typedef enum {
    KIBIO_AMPL_NONE     = 0,  /*!<  No amplifier VMP3 series */
    KIBIO_AMPL_2A       = 1,  /*!<  Amplifier 2 A VMP3 series */
    KIBIO_AMPL_1A       = 2,  /*!<  Amplifier 1 A VMP3 series */
    KIBIO_AMPL_5A       = 3,  /*!<  Amplifier 5 A VMP3 series */
    KIBIO_AMPL_10A      = 4,  /*!<  Amplifier 10 A VMP3 series */
    KIBIO_AMPL_20A      = 5,  /*!<  Amplifier 20 A VMP3 series */
    KIBIO_AMPL_HEUS     = 6,  /*!<  reserved VMP3 series */
    KIBIO_AMPL_LC       = 7,  /*!<  Low current amplifier VMP3 series */
    KIBIO_AMPL_80A      = 8,  /*!<  Amplifier 80 A VMP3 series */
    KIBIO_AMPL_4AI      = 9,  /*!<  Amplifier 4 A VMP3 series */
    KIBIO_AMPL_PAC      = 10, /*!<  Fuel Cell Tester VMP3 series */
    KIBIO_AMPL_4AI_VSP  = 11, /*!<  Amplifier 4 A (VSP instrument) VMP3 series */
    KIBIO_AMPL_LC_VSP   = 12, /*!<  Low current amplifier (VSP instrument) VMP3 series */
    KIBIO_AMPL_UNDEF    = 13, /*!<  Undefined amplifier VMP3 series */
    KIBIO_AMPL_MUIC     = 14, /*!<  reserved VMP3 series */
    KIBIO_AMPL_NONE_GIL = 15, /*!<  No amplifier VMP3 series */
    KIBIO_AMPL_8AI      = 16, /*!<  Amplifier 8 A VMP3 series */
    KIBIO_AMPL_LB500    = 17, /*!<  Amplifier LB500 VMP3 series */
    KIBIO_AMPL_100A5V   = 18, /*!<  Amplifier 100 A VMP3 series */
    KIBIO_AMPL_LB2000   = 19, /*!<  Amplifier LB2000 VMP3 series */
    KBIO_AMPL_1A48V     = 20, /*!<  Amplifier 1A 48V SP-300 series */
    KBIO_AMPL_4A10V     = 21  /*!<  Amplifier 4A 10V SP-300 series */
} TAmplifierType_e;

/** Intensity range */
typedef enum {
    KBIO_IRANGE_100pA   = 0,  /*!<  I range 100 pA SP-300 series */
    KBIO_IRANGE_1nA     = 1,  /*!<  I range 1 nA VMP3 / SP-300 series */
    KBIO_IRANGE_10nA    = 2,  /*!<  I range 10 nA VMP3 / SP-300 series */
    KBIO_IRANGE_100nA   = 3,  /*!<  I range 100 nA VMP3 / SP-300 series */
    KBIO_IRANGE_1uA     = 4,  /*!<  I range 1 uA VMP3 / SP-300 series */
    KBIO_IRANGE_10uA    = 5,  /*!<  I range 10 uA VMP3 / SP-300 series */
    KBIO_IRANGE_100uA   = 6,  /*!<  I range 100 uA VMP3 / SP-300 series */
    KBIO_IRANGE_1mA     = 7,  /*!<  I range 1 mA VMP3 / SP-300 series */
    KBIO_IRANGE_10mA    = 8,  /*!<  I range 10 mA VMP3 / SP-300 series */
    KBIO_IRANGE_100mA   = 9,  /*!<  I range 100 mA VMP3 / SP-300 series */
    KBIO_IRANGE_1A      = 10, /*!<  I range 1 A VMP3 / SP-300 series */
    KBIO_IRANGE_BOOSTER = 11, /*!<  Booster VMP3 / SP-300 series */
    KBIO_IRANGE_AUTO    = 12  /*!<  Auto range VMP3 / SP-300 series */
} TIntensityRange_e;

/** Voltage range */
typedef enum {
    KBIO_ERANGE_2_5  = 0, /*!<  +/- 2.5 V */
    KBIO_ERANGE_5    = 1, /*!<  +/- 5 V */
    KBIO_ERANGE_10   = 2, /*!<  +/- 10 V */
    KBIO_ERANGE_AUTO = 3  /*!<  Auto range */
} TVoltageRange_e;

/** Bandwidth */
typedef enum {
    KBIO_BW_1 = 1, /*!<  Bandwidth #1 */
    KBIO_BW_2 = 2, /*!<  Bandwidth #2 */
    KBIO_BW_3 = 3, /*!<  Bandwidth #3 */
    KBIO_BW_4 = 4, /*!<  Bandwidth #4 */
    KBIO_BW_5 = 5, /*!<  Bandwidth #5 */
    KBIO_BW_6 = 6, /*!<  Bandwidth #6 */
    KBIO_BW_7 = 7, /*!<  Bandwidth #7 */
    KBIO_BW_8 = 8, /*!<  Bandwidth #8 (only with SP-300 series) */
    KBIO_BW_9 = 9  /*!<  Bandwidth #9 (only with SP-300 series) */
} TBandwidth_e;

/** Electrode connection */
typedef enum {
    KBIO_CONN_STD = 0,     /*!<  Standard connection */
    KBIO_CONN_CETOGRND = 1 /*!<  CE to ground connection */
} TElectrodeConn_e;

/** Electrode Ground mode */
typedef enum {
    KBIO_MODE_GROUNDED = 0, /*!<  Grounded mode */
    KBIO_MODE_FLOATING = 1  /*!<  Floating mode */
} TElectrodeMode_e;

/** Technique IDs enumeration */
typedef enum {
    KBIO_TECHID_NONE            = 0,   /*!<  None */
    KBIO_TECHID_OCV             = 100, /*!<  Open Circuit Voltage (Rest) identifier */
    KBIO_TECHID_CA              = 101, /*!<  Chrono-amperometry identifier */
    KBIO_TECHID_CP              = 102, /*!<  Chrono-potentiometry identifier */
    KBIO_TECHID_CV              = 103, /*!<  Cyclic Voltammetry identifier */
    KBIO_TECHID_PEIS            = 104, /*!<  Potentio Electrochemical Impedance Spectroscopy identifier */
    KBIO_TECHID_POTPULSE        = 105, /*!<  (unused) */
    KBIO_TECHID_GALPULSE        = 106, /*!<  (unused) */
    KBIO_TECHID_GEIS            = 107, /*!<  Galvano Electrochemical Impedance Spectroscopy identifier */
    KBIO_TECHID_STACKPEIS_SLAVE = 108, /*!<  Potentio Electrochemical Impedance Spectroscopy on stack identifier */
    KBIO_TECHID_STACKPEIS       = 109, /*!<  Potentio Electrochemical Impedance Spectroscopy on stack identifier */
    KBIO_TECHID_CPOWER          = 110, /*!<  Constant Power identifier */
    KBIO_TECHID_CLOAD           = 111, /*!<  Constant Load identifier */
    KBIO_TECHID_FCT             = 112, /*!<  (unused) */
    KBIO_TECHID_SPEIS           = 113, /*!<  Staircase Potentio Electrochemical Impedance Spectroscopy identifier */
    KBIO_TECHID_SGEIS           = 114, /*!<  Staircase Galvano Electrochemical Impedance Spectroscopy identifier */
    KBIO_TECHID_STACKPDYN       = 115, /*!<  Potentio dynamic on stack identifier */
    KBIO_TECHID_STACKPDYN_SLAVE = 116, /*!<  Potentio dynamic on stack identifier */
    KBIO_TECHID_STACKGDYN       = 117, /*!<  Galvano dynamic on stack identifier */
    KBIO_TECHID_STACKGEIS_SLAVE = 118, /*!<  Galvano Electrochemical Impedance Spectroscopy on stack identifier */
    KBIO_TECHID_STACKGEIS       = 119, /*!<  Galvano Electrochemical Impedance Spectroscopy on stack identifier */
    KBIO_TECHID_STACKGDYN_SLAVE = 120, /*!<  Galvano dynamic on stack identifier */
    KBIO_TECHID_CPO             = 121, /*!<  (unused) */
    KBIO_TECHID_CGA             = 122, /*!<  (unused) */
    KBIO_TECHID_COKINE          = 123, /*!<  (unused) */
    KBIO_TECHID_PDYN            = 124, /*!<  Potentio dynamic identifier */
    KBIO_TECHID_GDYN            = 125, /*!<  Galvano dynamic identifier */
    KBIO_TECHID_CVA             = 126, /*!<  Cyclic Voltammetry Advanced identifier */
    KBIO_TECHID_DPV             = 127, /*!<  Differential Pulse Voltammetry identifier */
    KBIO_TECHID_SWV             = 128, /*!<  Square Wave Voltammetry identifier */
    KBIO_TECHID_NPV             = 129, /*!<  Normal Pulse Voltammetry identifier */
    KBIO_TECHID_RNPV            = 130, /*!<  Reverse Normal Pulse Voltammetry identifier */
    KBIO_TECHID_DNPV            = 131, /*!<  Differential Normal Pulse Voltammetry identifier */
    KBIO_TECHID_DPA             = 132, /*!<  Differential Pulse Amperometry identifier */
    KBIO_TECHID_EVT             = 133, /*!<  Ecorr vs. time identifier */
    KBIO_TECHID_LP              = 134, /*!<  Linear Polarization identifier */
    KBIO_TECHID_GC              = 135, /*!<  Generalized corrosion identifier */
    KBIO_TECHID_CPP             = 136, /*!<  Cyclic Potentiodynamic Polarization identifier */
    KBIO_TECHID_PDP             = 137, /*!<  Potentiodynamic Pitting identifier */
    KBIO_TECHID_PSP             = 138, /*!<  Potentiostatic Pitting identifier */
    KBIO_TECHID_ZRA             = 139, /*!<  Zero Resistance Ammeter identifier */
    KBIO_TECHID_MIR             = 140, /*!<  Manual IR identifier */
    KBIO_TECHID_PZIR            = 141, /*!<  IR Determination with Potentiostatic Impedance identifier */
    KBIO_TECHID_GZIR            = 142, /*!<  IR Determination with Galvanostatic Impedance identifier */
    KBIO_TECHID_LOOP            = 150, /*!<  Loop (used for linked techniques) identifier */
    KBIO_TECHID_TO              = 151, /*!<  Trigger Out identifier */
    KBIO_TECHID_TI              = 152, /*!<  Trigger In identifier */
    KBIO_TECHID_TOS             = 153, /*!<  Trigger Set identifier */
    KBIO_TECHID_CPLIMIT         = 155, /*!<  Chrono-potentiometry with limits identifier */
    KBIO_TECHID_GDYNLIMIT       = 156, /*!<  Galvano dynamic with limits identifier */
    KBIO_TECHID_CALIMIT         = 157, /*!<  Chrono-amperometry with limits identifier */
    KBIO_TECHID_PDYNLIMIT       = 158, /*!<  Potentio dynamic with limits identifier */
    KBIO_TECHID_LASV            = 159, /*!<  Large amplitude sinusoidal voltammetry */
    KBIO_TECHID_MP              = 167, /*!<  Modular Pulse */
    KBIO_TECHID_CASG            = 169, /*!<  Constant amplitude sinusoidal micro galvano polarization */
    KBIO_TECHID_CASP            = 170  /*!<  Constant amplitude sinusoidal micro potentio polarization */
} TTechniqueIdentifier_e;

/** Channel State */
typedef enum {
    KBIO_STATE_STOP  = 0, /*!<  Channel is stopped */
    KBIO_STATE_RUN   = 1, /*!<  Channel is running */
    KBIO_STATE_PAUSE = 2  /*!<  Channel is paused */

} TChannelState_e;

/** Parameter type */
typedef enum {
    PARAM_INT32   = 0, /*!<  Parameter type = int32 */
    PARAM_BOOLEAN = 1, /*!<  Parameter type = boolean */
    PARAM_SINGLE  = 2  /*!<  Parameter type = single */
} TParamType_e;

/** ECLib Error codes */
typedef enum {
    ERR_NOERROR = 0, /*!< No Error */
    
    /* General error codes */
    ERR_GEN_NOTCONNECTED          = -1,  /*!<  no instrument connected */
    ERR_GEN_CONNECTIONINPROGRESS  = -2,  /*!<  connection in progress */
    ERR_GEN_CHANNELNOTPLUGGED     = -3,  /*!<  selected channel(s) unplugged */
    ERR_GEN_INVALIDPARAMETERS     = -4,  /*!<  invalid function parameters */
    ERR_GEN_FILENOTEXISTS         = -5,  /*!<  selected file does not exist */
    ERR_GEN_FUNCTIONFAILED        = -6,  /*!<  function failed */
    ERR_GEN_NOCHANNELELECTED      = -7,  /*!<  no channel selected */
    ERR_GEN_INVALIDCONF           = -8,  /*!<  invalid instrument configuration */
    ERR_GEN_ECLAB_LOADED          = -9,  /*!<  EC-Lab firmware loaded on the instrument */
    ERR_GEN_LIBNOTCORRECTLYLOADED = -10, /*!<  library not correctly loaded in memory */
    ERR_GEN_USBLIBRARYERROR       = -11, /*!<  USB library not correctly loaded in memory */
    ERR_GEN_FUNCTIONINPROGRESS    = -12, /*!<  function of the library already in progress */
    ERR_GEN_CHANNEL_RUNNING       = -13, /*!<  selected channel(s) already used */
    ERR_GEN_DEVICE_NOTALLOWED     = -14, /*!<  device not allowed */
    ERR_GEN_UPDATEPARAMETERS      = -15, /*!<  Invalid update function parameters */

    /* Instrument error codes */
    ERR_INSTR_VMEERROR        = -101, /*!<  internal instrument communication failed */
    ERR_INSTR_TOOMANYDATA     = -102, /*!<  too many data to transfer from the instrument (device error) */
    ERR_INSTR_RESPNOTPOSSIBLE = -103, /*!<  selected channel(s) unplugged (device error) */

    /* Communication error codes */
    ERR_COMM_COMMFAILED         = -200, /*!<  communication failed with the instrument */
    ERR_COMM_CONNECTIONFAILED   = -201, /*!<  cannot establish connection with the instrument */
    ERR_COMM_WAITINGACK         = -202, /*!<  waiting for the instrument response */
    ERR_COMM_INVALIDIPADDRESS   = -203, /*!<  invalid IP address */
    ERR_COMM_ALLOCMEMFAILED     = -204, /*!<  cannot allocate memory in the instrument */
    ERR_COMM_LOADFIRMWAREFAILED = -205, /*!<  cannot load firmware into selected channel(s) */
    ERR_COMM_INCOMPATIBLESERVER = -206, /*!<  communication firmware not compatible with the library */
    ERR_COMM_MAXCONNREACHED     = -207, /*!<  maximum number of allowed connections reached */

    /* Firmware error codes */
    ERR_FIRM_FIRMFILENOTEXISTS    = -300, /*!<  cannot find kernel.bin file */
    ERR_FIRM_FIRMFILEACCESSFAILED = -301, /*!<  cannot read kernel.bin file */
    ERR_FIRM_FIRMINVALIDFILE      = -302, /*!<  invalid kernel.bin file */
    ERR_FIRM_FIRMLOADINGFAILED    = -303, /*!<  cannot load kernel.bin on the selected channel(s) */
    ERR_FIRM_XILFILENOTEXISTS     = -304, /*!<  cannot find x100_01.txt file */
    ERR_FIRM_XILFILEACCESSFAILED  = -305, /*!<  cannot read x100_01.txt file */
    ERR_FIRM_XILINVALIDFILE       = -306, /*!<  invalid x100_01.txt file */
    ERR_FIRM_XILLOADINGFAILED     = -307, /*!<  cannot load x100_01.txt file on the selected channel(s) */
    ERR_FIRM_FIRMWARENOTLOADED    = -308, /*!<  no firmware loaded on the selected channel(s) */
    ERR_FIRM_FIRMWAREINCOMPATIBLE = -309, /*!<  loaded firmware not compatible with the library */

    /* Technique error codes */
    ERR_TECH_ECCFILENOTEXISTS    = -400, /*!<  cannot find the selected ECC file */
    ERR_TECH_INCOMPATIBLEECC     = -401, /*!<  ECC file not compatible with the channel firmware */
    ERR_TECH_ECCFILECORRUPTED    = -402, /*!<  ECC file corrupted */
    ERR_TECH_LOADTECHNIQUEFAILED = -403, /*!<  cannot load the ECC file */
    ERR_TECH_DATACORRUPTED       = -404, /*!<  data returned by the instrument are corrupted */
    ERR_TECH_MEMFULL             = -405  /*!<  cannot load techniques: full memory */
} TErrorCodes_e;

/** @} */

#endif /* _BLSTRUCTS_H_ */
