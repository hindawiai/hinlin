<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */
#अगर_अघोषित __PVRUSB2_HDW_INTERNAL_H
#घोषणा __PVRUSB2_HDW_INTERNAL_H

/*

  This header sets up all the पूर्णांकernal काष्ठाures and definitions needed to
  track and coordinate the driver's पूर्णांकeraction with the hardware.  ONLY
  source files which actually implement part of that whole circus should be
  including this header.  Higher levels, like the बाह्यal layers to the
  various खुला APIs (V4L, sysfs, etc) should NOT ever include this
  निजी, पूर्णांकernal header.  This means that pvrusb2-hdw, pvrusb2-encoder,
  etc will include this, but pvrusb2-v4l should not.

*/

#समावेश <linux/videodev2.h>
#समावेश <linux/i2c.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश "pvrusb2-hdw.h"
#समावेश "pvrusb2-io.h"
#समावेश <media/v4l2-device.h>
#समावेश <media/drv-पूर्णांकf/cx2341x.h>
#समावेश <media/i2c/ir-kbd-i2c.h>
#समावेश "pvrusb2-devattr.h"

/* Legal values क्रम PVR2_CID_HSM */
#घोषणा PVR2_CVAL_HSM_FAIL 0
#घोषणा PVR2_CVAL_HSM_FULL 1
#घोषणा PVR2_CVAL_HSM_HIGH 2

#घोषणा PVR2_VID_ENDPOINT        0x84
#घोषणा PVR2_UNK_ENDPOINT        0x86    /* maybe raw yuv ? */
#घोषणा PVR2_VBI_ENDPOINT        0x88

#घोषणा PVR2_CTL_BUFFSIZE        64

#घोषणा FREQTABLE_SIZE 500

#घोषणा LOCK_TAKE(x) करो अणु mutex_lock(&x##_mutex); x##_held = !0; पूर्ण जबतक (0)
#घोषणा LOCK_GIVE(x) करो अणु x##_held = 0; mutex_unlock(&x##_mutex); पूर्ण जबतक (0)

प्रकार पूर्णांक (*pvr2_ctlf_is_dirty)(काष्ठा pvr2_ctrl *);
प्रकार व्योम (*pvr2_ctlf_clear_dirty)(काष्ठा pvr2_ctrl *);
प्रकार पूर्णांक (*pvr2_ctlf_check_value)(काष्ठा pvr2_ctrl *,पूर्णांक);
प्रकार पूर्णांक (*pvr2_ctlf_get_value)(काष्ठा pvr2_ctrl *,पूर्णांक *);
प्रकार पूर्णांक (*pvr2_ctlf_set_value)(काष्ठा pvr2_ctrl *,पूर्णांक msk,पूर्णांक val);
प्रकार पूर्णांक (*pvr2_ctlf_val_to_sym)(काष्ठा pvr2_ctrl *,पूर्णांक msk,पूर्णांक val,
				    अक्षर *,अचिन्हित पूर्णांक,अचिन्हित पूर्णांक *);
प्रकार पूर्णांक (*pvr2_ctlf_sym_to_val)(काष्ठा pvr2_ctrl *,
				    स्थिर अक्षर *,अचिन्हित पूर्णांक,
				    पूर्णांक *mskp,पूर्णांक *valp);
प्रकार अचिन्हित पूर्णांक (*pvr2_ctlf_get_v4lflags)(काष्ठा pvr2_ctrl *);

/* This काष्ठाure describes a specअगरic control.  A table of these is set up
   in pvrusb2-hdw.c. */
काष्ठा pvr2_ctl_info अणु
	/* Control's name suitable क्रम use as an identअगरier */
	स्थिर अक्षर *name;

	/* Short description of control */
	स्थिर अक्षर *desc;

	/* Control's implementation */
	pvr2_ctlf_get_value get_value;      /* Get its value */
	pvr2_ctlf_get_value get_def_value;  /* Get its शेष value */
	pvr2_ctlf_get_value get_min_value;  /* Get minimum allowed value */
	pvr2_ctlf_get_value get_max_value;  /* Get maximum allowed value */
	pvr2_ctlf_set_value set_value;      /* Set its value */
	pvr2_ctlf_check_value check_value;  /* Check that value is valid */
	pvr2_ctlf_val_to_sym val_to_sym;    /* Custom convert value->symbol */
	pvr2_ctlf_sym_to_val sym_to_val;    /* Custom convert symbol->value */
	pvr2_ctlf_is_dirty is_dirty;        /* Return true अगर dirty */
	pvr2_ctlf_clear_dirty clear_dirty;  /* Clear dirty state */
	pvr2_ctlf_get_v4lflags get_v4lflags;/* Retrieve v4l flags */

	/* Control's type (पूर्णांक, क्रमागत, biपंचांगask) */
	क्रमागत pvr2_ctl_type type;

	/* Associated V4L control ID, अगर any */
	पूर्णांक v4l_id;

	/* Associated driver पूर्णांकernal ID, अगर any */
	पूर्णांक पूर्णांकernal_id;

	/* Don't implicitly initialize this control's value */
	पूर्णांक skip_init;

	/* Starting value क्रम this control */
	पूर्णांक शेष_value;

	/* Type-specअगरic control inक्रमmation */
	जोड़ अणु
		काष्ठा अणु /* Integer control */
			दीर्घ min_value; /* lower limit */
			दीर्घ max_value; /* upper limit */
		पूर्ण type_पूर्णांक;
		काष्ठा अणु /* क्रमागतerated control */
			अचिन्हित पूर्णांक count;       /* क्रमागत value count */
			स्थिर अक्षर * स्थिर *value_names; /* symbol names */
		पूर्ण type_क्रमागत;
		काष्ठा अणु /* biपंचांगask control */
			अचिन्हित पूर्णांक valid_bits; /* bits in use */
			स्थिर अक्षर **bit_names;  /* symbol name/bit */
		पूर्ण type_biपंचांगask;
	पूर्ण def;
पूर्ण;


/* Same as pvr2_ctl_info, but includes storage क्रम the control description */
#घोषणा PVR2_CTLD_INFO_DESC_SIZE 32
काष्ठा pvr2_ctld_info अणु
	काष्ठा pvr2_ctl_info info;
	अक्षर desc[PVR2_CTLD_INFO_DESC_SIZE];
पूर्ण;

काष्ठा pvr2_ctrl अणु
	स्थिर काष्ठा pvr2_ctl_info *info;
	काष्ठा pvr2_hdw *hdw;
पूर्ण;



/* Disposition of firmware1 loading situation */
#घोषणा FW1_STATE_UNKNOWN 0
#घोषणा FW1_STATE_MISSING 1
#घोषणा FW1_STATE_FAILED 2
#घोषणा FW1_STATE_RELOAD 3
#घोषणा FW1_STATE_OK 4

/* What state the device is in अगर it is a hybrid */
#घोषणा PVR2_PATHWAY_UNKNOWN 0
#घोषणा PVR2_PATHWAY_ANALOG 1
#घोषणा PVR2_PATHWAY_DIGITAL 2

प्रकार पूर्णांक (*pvr2_i2c_func)(काष्ठा pvr2_hdw *,u8,u8 *,u16,u8 *, u16);
#घोषणा PVR2_I2C_FUNC_CNT 128

/* This काष्ठाure contains all state data directly needed to
   manipulate the hardware (as opposed to complying with a kernel
   पूर्णांकerface) */
काष्ठा pvr2_hdw अणु
	/* Underlying USB device handle */
	काष्ठा usb_device *usb_dev;
	काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf;

	/* Our handle पूर्णांकo the v4l2 sub-device architecture */
	काष्ठा v4l2_device v4l2_dev;
	/* Device description, anything that must adjust behavior based on
	   device specअगरic info will use inक्रमmation held here. */
	स्थिर काष्ठा pvr2_device_desc *hdw_desc;

	/* Kernel worker thपढ़ो handling */
	काष्ठा work_काष्ठा workpoll;     /* Update driver state */

	/* Video spigot */
	काष्ठा pvr2_stream *vid_stream;

	/* Mutex क्रम all hardware state control */
	काष्ठा mutex big_lock_mutex;
	पूर्णांक big_lock_held;  /* For debugging */

	/* This is a simple string which identअगरies the instance of this
	   driver.  It is unique within the set of existing devices, but
	   there is no attempt to keep the name consistent with the same
	   physical device each समय. */
	अक्षर name[32];

	/* This is a simple string which identअगरies the physical device
	   instance itself - अगर possible.  (If not possible, then it is
	   based on the specअगरic driver instance, similar to name above.)
	   The idea here is that userspace might hopefully be able to use
	   this recognize specअगरic tuners.  It will encode a serial number,
	   अगर available. */
	अक्षर identअगरier[32];

	/* I2C stuff */
	काष्ठा i2c_adapter i2c_adap;
	काष्ठा i2c_algorithm i2c_algo;
	pvr2_i2c_func i2c_func[PVR2_I2C_FUNC_CNT];
	पूर्णांक i2c_cx25840_hack_state;
	पूर्णांक i2c_linked;

	/* IR related */
	अचिन्हित पूर्णांक ir_scheme_active; /* IR scheme as seen from the outside */
	काष्ठा IR_i2c_init_data ir_init_data; /* params passed to IR modules */

	/* Frequency table */
	अचिन्हित पूर्णांक freqTable[FREQTABLE_SIZE];
	अचिन्हित पूर्णांक freqProgSlot;

	/* Stuff क्रम handling low level control पूर्णांकeraction with device */
	काष्ठा mutex ctl_lock_mutex;
	पूर्णांक ctl_lock_held;  /* For debugging */
	काष्ठा urb *ctl_ग_लिखो_urb;
	काष्ठा urb *ctl_पढ़ो_urb;
	अचिन्हित अक्षर *ctl_ग_लिखो_buffer;
	अचिन्हित अक्षर *ctl_पढ़ो_buffer;
	पूर्णांक ctl_ग_लिखो_pend_flag;
	पूर्णांक ctl_पढ़ो_pend_flag;
	पूर्णांक ctl_समयout_flag;
	काष्ठा completion ctl_करोne;
	अचिन्हित अक्षर cmd_buffer[PVR2_CTL_BUFFSIZE];
	पूर्णांक cmd_debug_state;               // Low level command debugging info
	अचिन्हित अक्षर cmd_debug_code;      //
	अचिन्हित पूर्णांक cmd_debug_ग_लिखो_len;  //
	अचिन्हित पूर्णांक cmd_debug_पढ़ो_len;   //

	/* Bits of state that describe what is going on with various parts
	   of the driver. */
	पूर्णांक state_pathway_ok;         /* Pathway config is ok */
	पूर्णांक state_encoder_ok;         /* Encoder is operational */
	पूर्णांक state_encoder_run;        /* Encoder is running */
	पूर्णांक state_encoder_config;     /* Encoder is configured */
	पूर्णांक state_encoder_रुकोok;     /* Encoder pre-रुको करोne */
	पूर्णांक state_encoder_runok;      /* Encoder has run क्रम >= .25 sec */
	पूर्णांक state_decoder_run;        /* Decoder is running */
	पूर्णांक state_decoder_पढ़ोy;      /* Decoder is stabilized & streamable */
	पूर्णांक state_usbstream_run;      /* FX2 is streaming */
	पूर्णांक state_decoder_quiescent;  /* Decoder idle क्रम minimal पूर्णांकerval */
	पूर्णांक state_pipeline_config;    /* Pipeline is configured */
	पूर्णांक state_pipeline_req;       /* Somebody wants to stream */
	पूर्णांक state_pipeline_छोड़ो;     /* Pipeline must be छोड़ोd */
	पूर्णांक state_pipeline_idle;      /* Pipeline not running */

	/* This is the master state of the driver.  It is the combined
	   result of other bits of state.  Examining this will indicate the
	   overall state of the driver.  Values here are one of
	   PVR2_STATE_xxxx */
	अचिन्हित पूर्णांक master_state;

	/* True अगर device led is currently on */
	पूर्णांक led_on;

	/* True अगर states must be re-evaluated */
	पूर्णांक state_stale;

	व्योम (*state_func)(व्योम *);
	व्योम *state_data;

	/* Timer क्रम measuring required decoder settling समय beक्रमe we're
	   allowed to fire it up again. */
	काष्ठा समयr_list quiescent_समयr;

	/* Timer क्रम measuring decoder stabilization समय, which is the
	   amount of समय we need to let the decoder run beक्रमe we can
	   trust its output (otherwise the encoder might see garbage and
	   then fail to start correctly). */
	काष्ठा समयr_list decoder_stabilization_समयr;

	/* Timer क्रम measuring encoder pre-रुको समय */
	काष्ठा समयr_list encoder_रुको_समयr;

	/* Timer क्रम measuring encoder minimum run समय */
	काष्ठा समयr_list encoder_run_समयr;

	/* Place to block जबतक रुकोing क्रम state changes */
	रुको_queue_head_t state_रुको_data;


	पूर्णांक क्रमce_dirty;        /* consider all controls dirty अगर true */
	पूर्णांक flag_ok;            /* device in known good state */
	पूर्णांक flag_modulefail;    /* true अगर at least one module failed to load */
	पूर्णांक flag_disconnected;  /* flag_ok == 0 due to disconnect */
	पूर्णांक flag_init_ok;       /* true अगर काष्ठाure is fully initialized */
	पूर्णांक fw1_state;          /* current situation with fw1 */
	पूर्णांक pathway_state;      /* one of PVR2_PATHWAY_xxx */
	पूर्णांक flag_decoder_missed;/* We've noticed missing decoder */
	पूर्णांक flag_tripped;       /* Indicates overall failure to start */

	अचिन्हित पूर्णांक decoder_client_id;

	// CPU firmware info (used to help find / save firmware data)
	अक्षर *fw_buffer;
	अचिन्हित पूर्णांक fw_size;
	पूर्णांक fw_cpu_flag; /* True अगर we are dealing with the CPU */

	/* Tuner / frequency control stuff */
	अचिन्हित पूर्णांक tuner_type;
	पूर्णांक tuner_updated;
	अचिन्हित पूर्णांक freqValTelevision;  /* Current freq क्रम tv mode */
	अचिन्हित पूर्णांक freqValRadio;       /* Current freq क्रम radio mode */
	अचिन्हित पूर्णांक freqSlotTelevision; /* Current slot क्रम tv mode */
	अचिन्हित पूर्णांक freqSlotRadio;      /* Current slot क्रम radio mode */
	अचिन्हित पूर्णांक freqSelector;       /* 0=radio 1=television */
	पूर्णांक freqDirty;

	/* Current tuner info - this inक्रमmation is polled from the I2C bus */
	काष्ठा v4l2_tuner tuner_संकेत_info;
	पूर्णांक tuner_संकेत_stale;

	/* Cropping capability info */
	काष्ठा v4l2_cropcap cropcap_info;
	पूर्णांक cropcap_stale;

	/* Video standard handling */
	v4l2_std_id std_mask_eeprom; // Hardware supported selections
	v4l2_std_id std_mask_avail;  // Which standards we may select from
	v4l2_std_id std_mask_cur;    // Currently selected standard(s)
	पूर्णांक std_क्रमागत_cur;            // selected standard क्रमागतeration value
	पूर्णांक std_dirty;               // True अगर std_mask_cur has changed
	काष्ठा pvr2_ctl_info std_info_क्रमागत;
	काष्ठा pvr2_ctl_info std_info_avail;
	काष्ठा pvr2_ctl_info std_info_cur;
	काष्ठा pvr2_ctl_info std_info_detect;

	// Generated string names, one per actual V4L2 standard
	स्थिर अक्षर *std_mask_ptrs[32];
	अक्षर std_mask_names[32][16];

	पूर्णांक unit_number;             /* ID क्रम driver instance */
	अचिन्हित दीर्घ serial_number; /* ID क्रम hardware itself */

	अक्षर bus_info[32]; /* Bus location info */

	/* Minor numbers used by v4l logic (yes, this is a hack, as there
	   should be no v4l junk here).  Probably a better way to करो this. */
	पूर्णांक v4l_minor_number_video;
	पूर्णांक v4l_minor_number_vbi;
	पूर्णांक v4l_minor_number_radio;

	/* Bit mask of PVR2_CVAL_INPUT choices which are valid क्रम the hardware */
	अचिन्हित पूर्णांक input_avail_mask;
	/* Bit mask of PVR2_CVAL_INPUT choices which are currently allowed */
	अचिन्हित पूर्णांक input_allowed_mask;

	/* Location of eeprom or a negative number अगर none */
	पूर्णांक eeprom_addr;

	क्रमागत pvr2_config active_stream_type;
	क्रमागत pvr2_config desired_stream_type;

	/* Control state needed क्रम cx2341x module */
	काष्ठा cx2341x_mpeg_params enc_cur_state;
	काष्ठा cx2341x_mpeg_params enc_ctl_state;
	/* True अगर an encoder attribute has changed */
	पूर्णांक enc_stale;
	/* True अगर an unsafe encoder attribute has changed */
	पूर्णांक enc_unsafe_stale;
	/* True अगर enc_cur_state is valid */
	पूर्णांक enc_cur_valid;

	/* Control state */
#घोषणा VCREATE_DATA(lab) पूर्णांक lab##_val; पूर्णांक lab##_dirty
	VCREATE_DATA(brightness);
	VCREATE_DATA(contrast);
	VCREATE_DATA(saturation);
	VCREATE_DATA(hue);
	VCREATE_DATA(volume);
	VCREATE_DATA(balance);
	VCREATE_DATA(bass);
	VCREATE_DATA(treble);
	VCREATE_DATA(mute);
	VCREATE_DATA(cropl);
	VCREATE_DATA(cropt);
	VCREATE_DATA(cropw);
	VCREATE_DATA(croph);
	VCREATE_DATA(input);
	VCREATE_DATA(audiomode);
	VCREATE_DATA(res_hor);
	VCREATE_DATA(res_ver);
	VCREATE_DATA(srate);
#अघोषित VCREATE_DATA

	काष्ठा pvr2_ctld_info *mpeg_ctrl_info;

	काष्ठा pvr2_ctrl *controls;
	अचिन्हित पूर्णांक control_cnt;
पूर्ण;

/* This function माला_लो the current frequency */
अचिन्हित दीर्घ pvr2_hdw_get_cur_freq(काष्ठा pvr2_hdw *);

व्योम pvr2_hdw_status_poll(काष्ठा pvr2_hdw *);

#पूर्ण_अगर /* __PVRUSB2_HDW_INTERNAL_H */
