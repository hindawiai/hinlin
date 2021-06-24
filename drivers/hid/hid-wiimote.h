<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __HID_WIIMOTE_H
#घोषणा __HID_WIIMOTE_H

/*
 * HID driver क्रम Nपूर्णांकenकरो Wii / Wii U peripherals
 * Copyright (c) 2011-2013 David Herrmann <dh.herrmann@gmail.com>
 */

/*
 */

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/input.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>

#घोषणा WIIMOTE_NAME "Nintendo Wii Remote"
#घोषणा WIIMOTE_बफ_मानE 32

#घोषणा WIIPROTO_FLAG_LED1		0x01
#घोषणा WIIPROTO_FLAG_LED2		0x02
#घोषणा WIIPROTO_FLAG_LED3		0x04
#घोषणा WIIPROTO_FLAG_LED4		0x08
#घोषणा WIIPROTO_FLAG_RUMBLE		0x10
#घोषणा WIIPROTO_FLAG_ACCEL		0x20
#घोषणा WIIPROTO_FLAG_IR_BASIC		0x40
#घोषणा WIIPROTO_FLAG_IR_EXT		0x80
#घोषणा WIIPROTO_FLAG_IR_FULL		0xc0 /* IR_BASIC | IR_EXT */
#घोषणा WIIPROTO_FLAG_EXT_PLUGGED	0x0100
#घोषणा WIIPROTO_FLAG_EXT_USED		0x0200
#घोषणा WIIPROTO_FLAG_EXT_ACTIVE	0x0400
#घोषणा WIIPROTO_FLAG_MP_PLUGGED	0x0800
#घोषणा WIIPROTO_FLAG_MP_USED		0x1000
#घोषणा WIIPROTO_FLAG_MP_ACTIVE		0x2000
#घोषणा WIIPROTO_FLAG_EXITING		0x4000
#घोषणा WIIPROTO_FLAG_DRM_LOCKED	0x8000
#घोषणा WIIPROTO_FLAG_BUILTIN_MP	0x010000
#घोषणा WIIPROTO_FLAG_NO_MP		0x020000
#घोषणा WIIPROTO_FLAG_PRO_CALIB_DONE	0x040000

#घोषणा WIIPROTO_FLAGS_LEDS (WIIPROTO_FLAG_LED1 | WIIPROTO_FLAG_LED2 | \
					WIIPROTO_FLAG_LED3 | WIIPROTO_FLAG_LED4)
#घोषणा WIIPROTO_FLAGS_IR (WIIPROTO_FLAG_IR_BASIC | WIIPROTO_FLAG_IR_EXT | \
							WIIPROTO_FLAG_IR_FULL)

/* वापस flag क्रम led \नum */
#घोषणा WIIPROTO_FLAG_LED(num) (WIIPROTO_FLAG_LED1 << (num - 1))

क्रमागत wiiproto_keys अणु
	WIIPROTO_KEY_LEFT,
	WIIPROTO_KEY_RIGHT,
	WIIPROTO_KEY_UP,
	WIIPROTO_KEY_DOWN,
	WIIPROTO_KEY_PLUS,
	WIIPROTO_KEY_MINUS,
	WIIPROTO_KEY_ONE,
	WIIPROTO_KEY_TWO,
	WIIPROTO_KEY_A,
	WIIPROTO_KEY_B,
	WIIPROTO_KEY_HOME,
	WIIPROTO_KEY_COUNT
पूर्ण;

क्रमागत wiimote_devtype अणु
	WIIMOTE_DEV_PENDING,
	WIIMOTE_DEV_UNKNOWN,
	WIIMOTE_DEV_GENERIC,
	WIIMOTE_DEV_GEN10,
	WIIMOTE_DEV_GEN20,
	WIIMOTE_DEV_BALANCE_BOARD,
	WIIMOTE_DEV_PRO_CONTROLLER,
	WIIMOTE_DEV_NUM,
पूर्ण;

क्रमागत wiimote_exttype अणु
	WIIMOTE_EXT_NONE,
	WIIMOTE_EXT_UNKNOWN,
	WIIMOTE_EXT_NUNCHUK,
	WIIMOTE_EXT_CLASSIC_CONTROLLER,
	WIIMOTE_EXT_BALANCE_BOARD,
	WIIMOTE_EXT_PRO_CONTROLLER,
	WIIMOTE_EXT_DRUMS,
	WIIMOTE_EXT_GUITAR,
	WIIMOTE_EXT_NUM,
पूर्ण;

क्रमागत wiimote_mptype अणु
	WIIMOTE_MP_NONE,
	WIIMOTE_MP_UNKNOWN,
	WIIMOTE_MP_SINGLE,
	WIIMOTE_MP_PASSTHROUGH_NUNCHUK,
	WIIMOTE_MP_PASSTHROUGH_CLASSIC,
पूर्ण;

काष्ठा wiimote_buf अणु
	__u8 data[HID_MAX_BUFFER_SIZE];
	माप_प्रकार size;
पूर्ण;

काष्ठा wiimote_queue अणु
	spinlock_t lock;
	काष्ठा work_काष्ठा worker;
	__u8 head;
	__u8 tail;
	काष्ठा wiimote_buf outq[WIIMOTE_बफ_मानE];
पूर्ण;

काष्ठा wiimote_state अणु
	spinlock_t lock;
	__u32 flags;
	__u8 accel_split[2];
	__u8 drm;
	__u8 devtype;
	__u8 exttype;
	__u8 mp;

	/* synchronous cmd requests */
	काष्ठा mutex sync;
	काष्ठा completion पढ़ोy;
	पूर्णांक cmd;
	__u32 opt;

	/* results of synchronous requests */
	__u8 cmd_battery;
	__u8 cmd_err;
	__u8 *cmd_पढ़ो_buf;
	__u8 cmd_पढ़ो_size;

	/* calibration/cache data */
	__u16 calib_bboard[4][3];
	__s16 calib_pro_sticks[4];
	__u8 pressure_drums[7];
	__u8 cache_rumble;
पूर्ण;

काष्ठा wiimote_data अणु
	काष्ठा hid_device *hdev;
	काष्ठा input_dev *input;
	काष्ठा work_काष्ठा rumble_worker;
	काष्ठा led_classdev *leds[4];
	काष्ठा input_dev *accel;
	काष्ठा input_dev *ir;
	काष्ठा घातer_supply *battery;
	काष्ठा घातer_supply_desc battery_desc;
	काष्ठा input_dev *mp;
	काष्ठा समयr_list समयr;
	काष्ठा wiimote_debug *debug;

	जोड़ अणु
		काष्ठा input_dev *input;
	पूर्ण extension;

	काष्ठा wiimote_queue queue;
	काष्ठा wiimote_state state;
	काष्ठा work_काष्ठा init_worker;
पूर्ण;

बाह्य bool wiimote_dpad_as_analog;

/* wiimote modules */

क्रमागत wiimod_module अणु
	WIIMOD_KEYS,
	WIIMOD_RUMBLE,
	WIIMOD_BATTERY,
	WIIMOD_LED1,
	WIIMOD_LED2,
	WIIMOD_LED3,
	WIIMOD_LED4,
	WIIMOD_ACCEL,
	WIIMOD_IR,
	WIIMOD_BUILTIN_MP,
	WIIMOD_NO_MP,
	WIIMOD_NUM,
	WIIMOD_शून्य = WIIMOD_NUM,
पूर्ण;

#घोषणा WIIMOD_FLAG_INPUT		0x0001
#घोषणा WIIMOD_FLAG_EXT8		0x0002
#घोषणा WIIMOD_FLAG_EXT16		0x0004

काष्ठा wiimod_ops अणु
	__u16 flags;
	अचिन्हित दीर्घ arg;
	पूर्णांक (*probe) (स्थिर काष्ठा wiimod_ops *ops,
		      काष्ठा wiimote_data *wdata);
	व्योम (*हटाओ) (स्थिर काष्ठा wiimod_ops *ops,
			काष्ठा wiimote_data *wdata);

	व्योम (*in_keys) (काष्ठा wiimote_data *wdata, स्थिर __u8 *keys);
	व्योम (*in_accel) (काष्ठा wiimote_data *wdata, स्थिर __u8 *accel);
	व्योम (*in_ir) (काष्ठा wiimote_data *wdata, स्थिर __u8 *ir, bool packed,
		       अचिन्हित पूर्णांक id);
	व्योम (*in_mp) (काष्ठा wiimote_data *wdata, स्थिर __u8 *mp);
	व्योम (*in_ext) (काष्ठा wiimote_data *wdata, स्थिर __u8 *ext);
पूर्ण;

बाह्य स्थिर काष्ठा wiimod_ops *wiimod_table[WIIMOD_NUM];
बाह्य स्थिर काष्ठा wiimod_ops *wiimod_ext_table[WIIMOTE_EXT_NUM];
बाह्य स्थिर काष्ठा wiimod_ops wiimod_mp;

/* wiimote requests */

क्रमागत wiiproto_reqs अणु
	WIIPROTO_REQ_शून्य = 0x0,
	WIIPROTO_REQ_RUMBLE = 0x10,
	WIIPROTO_REQ_LED = 0x11,
	WIIPROTO_REQ_DRM = 0x12,
	WIIPROTO_REQ_IR1 = 0x13,
	WIIPROTO_REQ_SREQ = 0x15,
	WIIPROTO_REQ_WMEM = 0x16,
	WIIPROTO_REQ_RMEM = 0x17,
	WIIPROTO_REQ_IR2 = 0x1a,
	WIIPROTO_REQ_STATUS = 0x20,
	WIIPROTO_REQ_DATA = 0x21,
	WIIPROTO_REQ_RETURN = 0x22,

	/* DRM_K: BB*2 */
	WIIPROTO_REQ_DRM_K = 0x30,

	/* DRM_KA: BB*2 AA*3 */
	WIIPROTO_REQ_DRM_KA = 0x31,

	/* DRM_KE: BB*2 EE*8 */
	WIIPROTO_REQ_DRM_KE = 0x32,

	/* DRM_KAI: BB*2 AA*3 II*12 */
	WIIPROTO_REQ_DRM_KAI = 0x33,

	/* DRM_KEE: BB*2 EE*19 */
	WIIPROTO_REQ_DRM_KEE = 0x34,

	/* DRM_KAE: BB*2 AA*3 EE*16 */
	WIIPROTO_REQ_DRM_KAE = 0x35,

	/* DRM_KIE: BB*2 II*10 EE*9 */
	WIIPROTO_REQ_DRM_KIE = 0x36,

	/* DRM_KAIE: BB*2 AA*3 II*10 EE*6 */
	WIIPROTO_REQ_DRM_KAIE = 0x37,

	/* DRM_E: EE*21 */
	WIIPROTO_REQ_DRM_E = 0x3d,

	/* DRM_SKAI1: BB*2 AA*1 II*18 */
	WIIPROTO_REQ_DRM_SKAI1 = 0x3e,

	/* DRM_SKAI2: BB*2 AA*1 II*18 */
	WIIPROTO_REQ_DRM_SKAI2 = 0x3f,

	WIIPROTO_REQ_MAX
पूर्ण;

#घोषणा dev_to_wii(pdev) hid_get_drvdata(to_hid_device(pdev))

व्योम __wiimote_schedule(काष्ठा wiimote_data *wdata);

बाह्य व्योम wiiproto_req_drm(काष्ठा wiimote_data *wdata, __u8 drm);
बाह्य व्योम wiiproto_req_rumble(काष्ठा wiimote_data *wdata, __u8 rumble);
बाह्य व्योम wiiproto_req_leds(काष्ठा wiimote_data *wdata, पूर्णांक leds);
बाह्य व्योम wiiproto_req_status(काष्ठा wiimote_data *wdata);
बाह्य व्योम wiiproto_req_accel(काष्ठा wiimote_data *wdata, __u8 accel);
बाह्य व्योम wiiproto_req_ir1(काष्ठा wiimote_data *wdata, __u8 flags);
बाह्य व्योम wiiproto_req_ir2(काष्ठा wiimote_data *wdata, __u8 flags);
बाह्य पूर्णांक wiimote_cmd_ग_लिखो(काष्ठा wiimote_data *wdata, __u32 offset,
						स्थिर __u8 *wmem, __u8 size);
बाह्य sमाप_प्रकार wiimote_cmd_पढ़ो(काष्ठा wiimote_data *wdata, __u32 offset,
							__u8 *rmem, __u8 size);

#घोषणा wiiproto_req_rreg(wdata, os, sz) \
				wiiproto_req_rmem((wdata), false, (os), (sz))
#घोषणा wiiproto_req_reeprom(wdata, os, sz) \
				wiiproto_req_rmem((wdata), true, (os), (sz))
बाह्य व्योम wiiproto_req_rmem(काष्ठा wiimote_data *wdata, bool eeprom,
						__u32 offset, __u16 size);

#अगर_घोषित CONFIG_DEBUG_FS

बाह्य पूर्णांक wiidebug_init(काष्ठा wiimote_data *wdata);
बाह्य व्योम wiidebug_deinit(काष्ठा wiimote_data *wdata);

#अन्यथा

अटल अंतरभूत पूर्णांक wiidebug_init(व्योम *u) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम wiidebug_deinit(व्योम *u) अणु पूर्ण

#पूर्ण_अगर

/* requires the state.lock spinlock to be held */
अटल अंतरभूत bool wiimote_cmd_pending(काष्ठा wiimote_data *wdata, पूर्णांक cmd,
								__u32 opt)
अणु
	वापस wdata->state.cmd == cmd && wdata->state.opt == opt;
पूर्ण

/* requires the state.lock spinlock to be held */
अटल अंतरभूत व्योम wiimote_cmd_complete(काष्ठा wiimote_data *wdata)
अणु
	wdata->state.cmd = WIIPROTO_REQ_शून्य;
	complete(&wdata->state.पढ़ोy);
पूर्ण

/* requires the state.lock spinlock to be held */
अटल अंतरभूत व्योम wiimote_cmd_पात(काष्ठा wiimote_data *wdata)
अणु
	/* Abort synchronous request by waking up the sleeping caller. But
	 * reset the state.cmd field to an invalid value so no further event
	 * handlers will work with it. */
	wdata->state.cmd = WIIPROTO_REQ_MAX;
	complete(&wdata->state.पढ़ोy);
पूर्ण

अटल अंतरभूत पूर्णांक wiimote_cmd_acquire(काष्ठा wiimote_data *wdata)
अणु
	वापस mutex_lock_पूर्णांकerruptible(&wdata->state.sync) ? -ERESTARTSYS : 0;
पूर्ण

अटल अंतरभूत व्योम wiimote_cmd_acquire_noपूर्णांक(काष्ठा wiimote_data *wdata)
अणु
	mutex_lock(&wdata->state.sync);
पूर्ण

/* requires the state.lock spinlock to be held */
अटल अंतरभूत व्योम wiimote_cmd_set(काष्ठा wiimote_data *wdata, पूर्णांक cmd,
								__u32 opt)
अणु
	reinit_completion(&wdata->state.पढ़ोy);
	wdata->state.cmd = cmd;
	wdata->state.opt = opt;
पूर्ण

अटल अंतरभूत व्योम wiimote_cmd_release(काष्ठा wiimote_data *wdata)
अणु
	mutex_unlock(&wdata->state.sync);
पूर्ण

अटल अंतरभूत पूर्णांक wiimote_cmd_रुको(काष्ठा wiimote_data *wdata)
अणु
	पूर्णांक ret;

	/* The completion acts as implicit memory barrier so we can safely
	 * assume that state.cmd is set on success/failure and isn't accessed
	 * by any other thपढ़ो, anymore. */

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&wdata->state.पढ़ोy, HZ);
	अगर (ret < 0)
		वापस -ERESTARTSYS;
	अन्यथा अगर (ret == 0)
		वापस -EIO;
	अन्यथा अगर (wdata->state.cmd != WIIPROTO_REQ_शून्य)
		वापस -EIO;
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक wiimote_cmd_रुको_noपूर्णांक(काष्ठा wiimote_data *wdata)
अणु
	अचिन्हित दीर्घ ret;

	/* no locking needed; see wiimote_cmd_रुको() */
	ret = रुको_क्रम_completion_समयout(&wdata->state.पढ़ोy, HZ);
	अगर (!ret)
		वापस -EIO;
	अन्यथा अगर (wdata->state.cmd != WIIPROTO_REQ_शून्य)
		वापस -EIO;
	अन्यथा
		वापस 0;
पूर्ण

#पूर्ण_अगर
