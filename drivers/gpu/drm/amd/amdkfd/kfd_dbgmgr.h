<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित KFD_DBGMGR_H_
#घोषणा KFD_DBGMGR_H_

#समावेश "kfd_priv.h"

/* must align with hsakmttypes definition */
#आशय pack(push, 4)

क्रमागत HSA_DBG_WAVEOP अणु
	HSA_DBG_WAVEOP_HALT = 1,   /* Halts a wavefront */
	HSA_DBG_WAVEOP_RESUME = 2, /* Resumes a wavefront */
	HSA_DBG_WAVEOP_KILL = 3,   /* Kills a wavefront */
	HSA_DBG_WAVEOP_DEBUG = 4,  /* Causes wavefront to enter dbg mode */
	HSA_DBG_WAVEOP_TRAP = 5,   /* Causes wavefront to take a trap */
	HSA_DBG_NUM_WAVEOP = 5,
	HSA_DBG_MAX_WAVEOP = 0xFFFFFFFF
पूर्ण;

क्रमागत HSA_DBG_WAVEMODE अणु
	/* send command to a single wave */
	HSA_DBG_WAVEMODE_SINGLE = 0,
	/*
	 * Broadcast to all wavefronts of all processes is not
	 * supported क्रम HSA user mode
	 */

	/* send to waves within current process */
	HSA_DBG_WAVEMODE_BROADCAST_PROCESS = 2,
	/* send to waves within current process on CU  */
	HSA_DBG_WAVEMODE_BROADCAST_PROCESS_CU = 3,
	HSA_DBG_NUM_WAVEMODE = 3,
	HSA_DBG_MAX_WAVEMODE = 0xFFFFFFFF
पूर्ण;

क्रमागत HSA_DBG_WAVEMSG_TYPE अणु
	HSA_DBG_WAVEMSG_AUTO = 0,
	HSA_DBG_WAVEMSG_USER = 1,
	HSA_DBG_WAVEMSG_ERROR = 2,
	HSA_DBG_NUM_WAVEMSG,
	HSA_DBG_MAX_WAVEMSG = 0xFFFFFFFF
पूर्ण;

क्रमागत HSA_DBG_WATCH_MODE अणु
	HSA_DBG_WATCH_READ = 0,		/* Read operations only */
	HSA_DBG_WATCH_NONREAD = 1,	/* Write or Atomic operations only */
	HSA_DBG_WATCH_ATOMIC = 2,	/* Atomic Operations only */
	HSA_DBG_WATCH_ALL = 3,		/* Read, Write or Atomic operations */
	HSA_DBG_WATCH_NUM,
	HSA_DBG_WATCH_SIZE = 0xFFFFFFFF
पूर्ण;

/* This काष्ठाure is hardware specअगरic and may change in the future */
काष्ठा HsaDbgWaveMsgAMDGen2 अणु
	जोड़ अणु
		काष्ठा ui32 अणु
			uपूर्णांक32_t UserData:8;	/* user data */
			uपूर्णांक32_t ShaderArray:1;	/* Shader array */
			uपूर्णांक32_t Priv:1;	/* Privileged */
			uपूर्णांक32_t Reserved0:4;	/* Reserved, should be 0 */
			uपूर्णांक32_t WaveId:4;	/* wave id */
			uपूर्णांक32_t SIMD:2;	/* SIMD id */
			uपूर्णांक32_t HSACU:4;	/* Compute unit */
			uपूर्णांक32_t ShaderEngine:2;/* Shader engine */
			uपूर्णांक32_t MessageType:2;	/* see HSA_DBG_WAVEMSG_TYPE */
			uपूर्णांक32_t Reserved1:4;	/* Reserved, should be 0 */
		पूर्ण ui32;
		uपूर्णांक32_t Value;
	पूर्ण;
	uपूर्णांक32_t Reserved2;
पूर्ण;

जोड़ HsaDbgWaveMessageAMD अणु
	काष्ठा HsaDbgWaveMsgAMDGen2 WaveMsgInfoGen2;
	/* क्रम future HsaDbgWaveMsgAMDGen3; */
पूर्ण;

काष्ठा HsaDbgWaveMessage अणु
	व्योम *MemoryVA;		/* ptr to associated host-accessible data */
	जोड़ HsaDbgWaveMessageAMD DbgWaveMsg;
पूर्ण;

/*
 * TODO: This definitions to be MOVED to kfd_event, once it is implemented.
 *
 * HSA sync primitive, Event and HW Exception notअगरication API definitions.
 * The API functions allow the runसमय to define a so-called sync-primitive,
 * a SW object combining a user-mode provided "syncvar" and a scheduler event
 * that can be संकेतed through a defined GPU पूर्णांकerrupt. A syncvar is
 * a process भव memory location of a certain size that can be accessed
 * by CPU and GPU shader code within the process to set and query the content
 * within that memory. The definition of the content is determined by the HSA
 * runसमय and potentially GPU shader code पूर्णांकerfacing with the HSA runसमय.
 * The syncvar values may be commonly written through an PM4 WRITE_DATA packet
 * in the user mode inकाष्ठाion stream. The OS scheduler event is typically
 * associated and संकेतed by an पूर्णांकerrupt issued by the GPU, but other HSA
 * प्रणाली पूर्णांकerrupt conditions from other HW (e.g. IOMMUv2) may be surfaced
 * by the KFD by this mechanism, too.
 */

/* these are the new definitions क्रम events */
क्रमागत HSA_EVENTTYPE अणु
	HSA_EVENTTYPE_SIGNAL = 0,	/* user-mode generated GPU संकेत */
	HSA_EVENTTYPE_NODECHANGE = 1,	/* HSA node change (attach/detach) */
	HSA_EVENTTYPE_DEVICESTATECHANGE = 2,	/* HSA device state change
						 * (start/stop)
						 */
	HSA_EVENTTYPE_HW_EXCEPTION = 3,	/* GPU shader exception event */
	HSA_EVENTTYPE_SYSTEM_EVENT = 4,	/* GPU SYSCALL with parameter info */
	HSA_EVENTTYPE_DEBUG_EVENT = 5,	/* GPU संकेत क्रम debugging */
	HSA_EVENTTYPE_PROखाता_EVENT = 6,/* GPU संकेत क्रम profiling */
	HSA_EVENTTYPE_QUEUE_EVENT = 7,	/* GPU संकेत queue idle state
					 * (EOP pm4)
					 */
	/* ...  */
	HSA_EVENTTYPE_MAXID,
	HSA_EVENTTYPE_TYPE_SIZE = 0xFFFFFFFF
पूर्ण;

/* Sub-definitions क्रम various event types: Syncvar */
काष्ठा HsaSyncVar अणु
	जोड़ SyncVar अणु
		व्योम *UserData;	/* poपूर्णांकer to user mode data */
		uपूर्णांक64_t UserDataPtrValue; /* 64bit compatibility of value */
	पूर्ण SyncVar;
	uपूर्णांक64_t SyncVarSize;
पूर्ण;

/* Sub-definitions क्रम various event types: NodeChange */

क्रमागत HSA_EVENTTYPE_NODECHANGE_FLAGS अणु
	HSA_EVENTTYPE_NODECHANGE_ADD = 0,
	HSA_EVENTTYPE_NODECHANGE_REMOVE = 1,
	HSA_EVENTTYPE_NODECHANGE_SIZE = 0xFFFFFFFF
पूर्ण;

काष्ठा HsaNodeChange अणु
	/* HSA node added/हटाओd on the platक्रमm */
	क्रमागत HSA_EVENTTYPE_NODECHANGE_FLAGS Flags;
पूर्ण;

/* Sub-definitions क्रम various event types: DeviceStateChange */
क्रमागत HSA_EVENTTYPE_DEVICESTATECHANGE_FLAGS अणु
	/* device started (and available) */
	HSA_EVENTTYPE_DEVICESTATUSCHANGE_START = 0,
	/* device stopped (i.e. unavailable) */
	HSA_EVENTTYPE_DEVICESTATUSCHANGE_STOP = 1,
	HSA_EVENTTYPE_DEVICESTATUSCHANGE_SIZE = 0xFFFFFFFF
पूर्ण;

क्रमागत HSA_DEVICE अणु
	HSA_DEVICE_CPU = 0,
	HSA_DEVICE_GPU = 1,
	MAX_HSA_DEVICE = 2
पूर्ण;

काष्ठा HsaDeviceStateChange अणु
	uपूर्णांक32_t NodeId;	/* F-NUMA node that contains the device */
	क्रमागत HSA_DEVICE Device;	/* device type: GPU or CPU */
	क्रमागत HSA_EVENTTYPE_DEVICESTATECHANGE_FLAGS Flags; /* event flags */
पूर्ण;

काष्ठा HsaEventData अणु
	क्रमागत HSA_EVENTTYPE EventType; /* event type */
	जोड़ EventData अणु
		/*
		 * वापस data associated with HSA_EVENTTYPE_SIGNAL
		 * and other events
		 */
		काष्ठा HsaSyncVar SyncVar;

		/* data associated with HSA_EVENTTYPE_NODE_CHANGE */
		काष्ठा HsaNodeChange NodeChangeState;

		/* data associated with HSA_EVENTTYPE_DEVICE_STATE_CHANGE */
		काष्ठा HsaDeviceStateChange DeviceState;
	पूर्ण EventData;

	/* the following data entries are पूर्णांकernal to the KFD & thunk itself */

	/* पूर्णांकernal thunk store क्रम Event data (OsEventHandle) */
	uपूर्णांक64_t HWData1;
	/* पूर्णांकernal thunk store क्रम Event data (HWAddress) */
	uपूर्णांक64_t HWData2;
	/* पूर्णांकernal thunk store क्रम Event data (HWData) */
	uपूर्णांक32_t HWData3;
पूर्ण;

काष्ठा HsaEventDescriptor अणु
	/* event type to allocate */
	क्रमागत HSA_EVENTTYPE EventType;
	/* H-NUMA node containing GPU device that is event source */
	uपूर्णांक32_t NodeId;
	/* poपूर्णांकer to user mode syncvar data, syncvar->UserDataPtrValue
	 * may be शून्य
	 */
	काष्ठा HsaSyncVar SyncVar;
पूर्ण;

काष्ठा HsaEvent अणु
	uपूर्णांक32_t EventId;
	काष्ठा HsaEventData EventData;
पूर्ण;

#आशय pack(pop)

क्रमागत DBGDEV_TYPE अणु
	DBGDEV_TYPE_ILLEGAL = 0,
	DBGDEV_TYPE_NODIQ = 1,
	DBGDEV_TYPE_DIQ = 2,
	DBGDEV_TYPE_TEST = 3
पूर्ण;

काष्ठा dbg_address_watch_info अणु
	काष्ठा kfd_process *process;
	क्रमागत HSA_DBG_WATCH_MODE *watch_mode;
	uपूर्णांक64_t *watch_address;
	uपूर्णांक64_t *watch_mask;
	काष्ठा HsaEvent *watch_event;
	uपूर्णांक32_t num_watch_poपूर्णांकs;
पूर्ण;

काष्ठा dbg_wave_control_info अणु
	काष्ठा kfd_process *process;
	uपूर्णांक32_t trapId;
	क्रमागत HSA_DBG_WAVEOP opeअक्रम;
	क्रमागत HSA_DBG_WAVEMODE mode;
	काष्ठा HsaDbgWaveMessage dbgWave_msg;
पूर्ण;

काष्ठा kfd_dbgdev अणु

	/* The device that owns this data. */
	काष्ठा kfd_dev *dev;

	/* kernel queue क्रम DIQ */
	काष्ठा kernel_queue *kq;

	/* a poपूर्णांकer to the pqm of the calling process */
	काष्ठा process_queue_manager *pqm;

	/* type of debug device ( DIQ, non DIQ, etc. ) */
	क्रमागत DBGDEV_TYPE type;

	/* भवized function poपूर्णांकers to device dbg */
	पूर्णांक (*dbgdev_रेजिस्टर)(काष्ठा kfd_dbgdev *dbgdev);
	पूर्णांक (*dbgdev_unरेजिस्टर)(काष्ठा kfd_dbgdev *dbgdev);
	पूर्णांक (*dbgdev_address_watch)(काष्ठा kfd_dbgdev *dbgdev,
				काष्ठा dbg_address_watch_info *adw_info);
	पूर्णांक (*dbgdev_wave_control)(काष्ठा kfd_dbgdev *dbgdev,
				काष्ठा dbg_wave_control_info *wac_info);

पूर्ण;

काष्ठा kfd_dbgmgr अणु
	u32 pasid;
	काष्ठा kfd_dev *dev;
	काष्ठा kfd_dbgdev *dbgdev;
पूर्ण;

/* prototypes क्रम debug manager functions */
काष्ठा mutex *kfd_get_dbgmgr_mutex(व्योम);
व्योम kfd_dbgmgr_destroy(काष्ठा kfd_dbgmgr *pmgr);
bool kfd_dbgmgr_create(काष्ठा kfd_dbgmgr **ppmgr, काष्ठा kfd_dev *pdev);
दीर्घ kfd_dbgmgr_रेजिस्टर(काष्ठा kfd_dbgmgr *pmgr, काष्ठा kfd_process *p);
दीर्घ kfd_dbgmgr_unरेजिस्टर(काष्ठा kfd_dbgmgr *pmgr, काष्ठा kfd_process *p);
दीर्घ kfd_dbgmgr_wave_control(काष्ठा kfd_dbgmgr *pmgr,
				काष्ठा dbg_wave_control_info *wac_info);
दीर्घ kfd_dbgmgr_address_watch(काष्ठा kfd_dbgmgr *pmgr,
			काष्ठा dbg_address_watch_info *adw_info);
#पूर्ण_अगर /* KFD_DBGMGR_H_ */
