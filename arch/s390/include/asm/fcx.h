<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Functions क्रम assembling fcx enabled I/O control blocks.
 *
 *    Copyright IBM Corp. 2008
 *    Author(s): Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#अगर_अघोषित _ASM_S390_FCX_H
#घोषणा _ASM_S390_FCX_H

#समावेश <linux/types.h>

#घोषणा TCW_FORMAT_DEFAULT		0
#घोषणा TCW_TIDAW_FORMAT_DEFAULT	0
#घोषणा TCW_FLAGS_INPUT_TIDA		(1 << (23 - 5))
#घोषणा TCW_FLAGS_TCCB_TIDA		(1 << (23 - 6))
#घोषणा TCW_FLAGS_OUTPUT_TIDA		(1 << (23 - 7))
#घोषणा TCW_FLAGS_TIDAW_FORMAT(x)	((x) & 3) << (23 - 9)
#घोषणा TCW_FLAGS_GET_TIDAW_FORMAT(x)	(((x) >> (23 - 9)) & 3)

/**
 * काष्ठा tcw - Transport Control Word (TCW)
 * @क्रमmat: TCW क्रमmat
 * @flags: TCW flags
 * @tccbl: Transport-Command-Control-Block Length
 * @r: Read Operations
 * @w: Write Operations
 * @output: Output-Data Address
 * @input: Input-Data Address
 * @tsb: Transport-Status-Block Address
 * @tccb: Transport-Command-Control-Block Address
 * @output_count: Output Count
 * @input_count: Input Count
 * @पूर्णांकrg: Interrogate TCW Address
 */
काष्ठा tcw अणु
	u32 क्रमmat:2;
	u32 :6;
	u32 flags:24;
	u32 :8;
	u32 tccbl:6;
	u32 r:1;
	u32 w:1;
	u32 :16;
	u64 output;
	u64 input;
	u64 tsb;
	u64 tccb;
	u32 output_count;
	u32 input_count;
	u32 :32;
	u32 :32;
	u32 :32;
	u32 पूर्णांकrg;
पूर्ण __attribute__ ((packed, aligned(64)));

#घोषणा TIDAW_FLAGS_LAST		(1 << (7 - 0))
#घोषणा TIDAW_FLAGS_SKIP		(1 << (7 - 1))
#घोषणा TIDAW_FLAGS_DATA_INT		(1 << (7 - 2))
#घोषणा TIDAW_FLAGS_TTIC		(1 << (7 - 3))
#घोषणा TIDAW_FLAGS_INSERT_CBC		(1 << (7 - 4))

/**
 * काष्ठा tidaw - Transport-Indirect-Addressing Word (TIDAW)
 * @flags: TIDAW flags. Can be an arithmetic OR of the following स्थिरants:
 * %TIDAW_FLAGS_LAST, %TIDAW_FLAGS_SKIP, %TIDAW_FLAGS_DATA_INT,
 * %TIDAW_FLAGS_TTIC, %TIDAW_FLAGS_INSERT_CBC
 * @count: Count
 * @addr: Address
 */
काष्ठा tidaw अणु
	u32 flags:8;
	u32 :24;
	u32 count;
	u64 addr;
पूर्ण __attribute__ ((packed, aligned(16)));

/**
 * काष्ठा tsa_iostat - I/O-Status Transport-Status Area (IO-Stat TSA)
 * @dev_समय: Device Time
 * @def_समय: Defer Time
 * @queue_समय: Queue Time
 * @dev_busy_समय: Device-Busy Time
 * @dev_act_समय: Device-Active-Only Time
 * @sense: Sense Data (अगर present)
 */
काष्ठा tsa_iostat अणु
	u32 dev_समय;
	u32 def_समय;
	u32 queue_समय;
	u32 dev_busy_समय;
	u32 dev_act_समय;
	u8 sense[32];
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा tsa_ddpcs - Device-Detected-Program-Check Transport-Status Area (DDPC TSA)
 * @rc: Reason Code
 * @rcq: Reason Code Qualअगरier
 * @sense: Sense Data (अगर present)
 */
काष्ठा tsa_ddpc अणु
	u32 :24;
	u32 rc:8;
	u8 rcq[16];
	u8 sense[32];
पूर्ण __attribute__ ((packed));

#घोषणा TSA_INTRG_FLAGS_CU_STATE_VALID		(1 << (7 - 0))
#घोषणा TSA_INTRG_FLAGS_DEV_STATE_VALID		(1 << (7 - 1))
#घोषणा TSA_INTRG_FLAGS_OP_STATE_VALID		(1 << (7 - 2))

/**
 * काष्ठा tsa_पूर्णांकrg - Interrogate Transport-Status Area (Intrg. TSA)
 * @क्रमmat: Format
 * @flags: Flags. Can be an arithmetic OR of the following स्थिरants:
 * %TSA_INTRG_FLAGS_CU_STATE_VALID, %TSA_INTRG_FLAGS_DEV_STATE_VALID,
 * %TSA_INTRG_FLAGS_OP_STATE_VALID
 * @cu_state: Controle-Unit State
 * @dev_state: Device State
 * @op_state: Operation State
 * @sd_info: State-Dependent Inक्रमmation
 * @dl_id: Device-Level Identअगरier
 * @dd_data: Device-Dependent Data
 */
काष्ठा tsa_पूर्णांकrg अणु
	u32 क्रमmat:8;
	u32 flags:8;
	u32 cu_state:8;
	u32 dev_state:8;
	u32 op_state:8;
	u32 :24;
	u8 sd_info[12];
	u32 dl_id;
	u8 dd_data[28];
पूर्ण __attribute__ ((packed));

#घोषणा TSB_FORMAT_NONE		0
#घोषणा TSB_FORMAT_IOSTAT	1
#घोषणा TSB_FORMAT_DDPC		2
#घोषणा TSB_FORMAT_INTRG	3

#घोषणा TSB_FLAGS_DCW_OFFSET_VALID	(1 << (7 - 0))
#घोषणा TSB_FLAGS_COUNT_VALID		(1 << (7 - 1))
#घोषणा TSB_FLAGS_CACHE_MISS		(1 << (7 - 2))
#घोषणा TSB_FLAGS_TIME_VALID		(1 << (7 - 3))
#घोषणा TSB_FLAGS_FORMAT(x)		((x) & 7)
#घोषणा TSB_FORMAT(t)			((t)->flags & 7)

/**
 * काष्ठा tsb - Transport-Status Block (TSB)
 * @length: Length
 * @flags: Flags. Can be an arithmetic OR of the following स्थिरants:
 * %TSB_FLAGS_DCW_OFFSET_VALID, %TSB_FLAGS_COUNT_VALID, %TSB_FLAGS_CACHE_MISS,
 * %TSB_FLAGS_TIME_VALID
 * @dcw_offset: DCW Offset
 * @count: Count
 * @tsa: Transport-Status-Area
 */
काष्ठा tsb अणु
	u32 length:8;
	u32 flags:8;
	u32 dcw_offset:16;
	u32 count;
	u32 :32;
	जोड़ अणु
		काष्ठा tsa_iostat iostat;
		काष्ठा tsa_ddpc ddpc;
		काष्ठा tsa_पूर्णांकrg पूर्णांकrg;
	पूर्ण __attribute__ ((packed)) tsa;
पूर्ण __attribute__ ((packed, aligned(8)));

#घोषणा DCW_INTRG_FORMAT_DEFAULT	0

#घोषणा DCW_INTRG_RC_UNSPECIFIED	0
#घोषणा DCW_INTRG_RC_TIMEOUT		1

#घोषणा DCW_INTRG_RCQ_UNSPECIFIED	0
#घोषणा DCW_INTRG_RCQ_PRIMARY		1
#घोषणा DCW_INTRG_RCQ_SECONDARY		2

#घोषणा DCW_INTRG_FLAGS_MPM		(1 << (7 - 0))
#घोषणा DCW_INTRG_FLAGS_PPR		(1 << (7 - 1))
#घोषणा DCW_INTRG_FLAGS_CRIT		(1 << (7 - 2))

/**
 * काष्ठा dcw_पूर्णांकrg_data - Interrogate DCW data
 * @क्रमmat: Format. Should be %DCW_INTRG_FORMAT_DEFAULT
 * @rc: Reason Code. Can be one of %DCW_INTRG_RC_UNSPECIFIED,
 * %DCW_INTRG_RC_TIMEOUT
 * @rcq: Reason Code Qualअगरier: Can be one of %DCW_INTRG_RCQ_UNSPECIFIED,
 * %DCW_INTRG_RCQ_PRIMARY, %DCW_INTRG_RCQ_SECONDARY
 * @lpm: Logical-Path Mask
 * @pam: Path-Available Mask
 * @pim: Path-Installed Mask
 * @समयout: Timeout
 * @flags: Flags. Can be an arithmetic OR of %DCW_INTRG_FLAGS_MPM,
 * %DCW_INTRG_FLAGS_PPR, %DCW_INTRG_FLAGS_CRIT
 * @समय: Time
 * @prog_id: Program Identअगरier
 * @prog_data: Program-Dependent Data
 */
काष्ठा dcw_पूर्णांकrg_data अणु
	u32 क्रमmat:8;
	u32 rc:8;
	u32 rcq:8;
	u32 lpm:8;
	u32 pam:8;
	u32 pim:8;
	u32 समयout:16;
	u32 flags:8;
	u32 :24;
	u32 :32;
	u64 समय;
	u64 prog_id;
	u8  prog_data[0];
पूर्ण __attribute__ ((packed));

#घोषणा DCW_FLAGS_CC		(1 << (7 - 1))

#घोषणा DCW_CMD_WRITE		0x01
#घोषणा DCW_CMD_READ		0x02
#घोषणा DCW_CMD_CONTROL		0x03
#घोषणा DCW_CMD_SENSE		0x04
#घोषणा DCW_CMD_SENSE_ID	0xe4
#घोषणा DCW_CMD_INTRG		0x40

/**
 * काष्ठा dcw - Device-Command Word (DCW)
 * @cmd: Command Code. Can be one of %DCW_CMD_WRITE, %DCW_CMD_READ,
 * %DCW_CMD_CONTROL, %DCW_CMD_SENSE, %DCW_CMD_SENSE_ID, %DCW_CMD_INTRG
 * @flags: Flags. Can be an arithmetic OR of %DCW_FLAGS_CC
 * @cd_count: Control-Data Count
 * @count: Count
 * @cd: Control Data
 */
काष्ठा dcw अणु
	u32 cmd:8;
	u32 flags:8;
	u32 :8;
	u32 cd_count:8;
	u32 count;
	u8 cd[0];
पूर्ण __attribute__ ((packed));

#घोषणा TCCB_FORMAT_DEFAULT	0x7f
#घोषणा TCCB_MAX_DCW		30
#घोषणा TCCB_MAX_SIZE		(माप(काष्ठा tccb_tcah) + \
				 TCCB_MAX_DCW * माप(काष्ठा dcw) + \
				 माप(काष्ठा tccb_tcat))
#घोषणा TCCB_SAC_DEFAULT	0x1ffe
#घोषणा TCCB_SAC_INTRG		0x1fff

/**
 * काष्ठा tccb_tcah - Transport-Command-Area Header (TCAH)
 * @क्रमmat: Format. Should be %TCCB_FORMAT_DEFAULT
 * @tcal: Transport-Command-Area Length
 * @sac: Service-Action Code. Can be one of %TCCB_SAC_DEFAULT, %TCCB_SAC_INTRG
 * @prio: Priority
 */
काष्ठा tccb_tcah अणु
	u32 क्रमmat:8;
	u32 :24;
	u32 :24;
	u32 tcal:8;
	u32 sac:16;
	u32 :8;
	u32 prio:8;
	u32 :32;
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा tccb_tcat - Transport-Command-Area Trailer (TCAT)
 * @count: Transport Count
 */
काष्ठा tccb_tcat अणु
	u32 :32;
	u32 count;
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा tccb - (partial) Transport-Command-Control Block (TCCB)
 * @tcah: TCAH
 * @tca: Transport-Command Area
 */
काष्ठा tccb अणु
	काष्ठा tccb_tcah tcah;
	u8 tca[0];
पूर्ण __attribute__ ((packed, aligned(8)));

काष्ठा tcw *tcw_get_पूर्णांकrg(काष्ठा tcw *tcw);
व्योम *tcw_get_data(काष्ठा tcw *tcw);
काष्ठा tccb *tcw_get_tccb(काष्ठा tcw *tcw);
काष्ठा tsb *tcw_get_tsb(काष्ठा tcw *tcw);

व्योम tcw_init(काष्ठा tcw *tcw, पूर्णांक r, पूर्णांक w);
व्योम tcw_finalize(काष्ठा tcw *tcw, पूर्णांक num_tidaws);

व्योम tcw_set_पूर्णांकrg(काष्ठा tcw *tcw, काष्ठा tcw *पूर्णांकrg_tcw);
व्योम tcw_set_data(काष्ठा tcw *tcw, व्योम *data, पूर्णांक use_tidal);
व्योम tcw_set_tccb(काष्ठा tcw *tcw, काष्ठा tccb *tccb);
व्योम tcw_set_tsb(काष्ठा tcw *tcw, काष्ठा tsb *tsb);

व्योम tccb_init(काष्ठा tccb *tccb, माप_प्रकार tccb_size, u32 sac);
व्योम tsb_init(काष्ठा tsb *tsb);
काष्ठा dcw *tccb_add_dcw(काष्ठा tccb *tccb, माप_प्रकार tccb_size, u8 cmd, u8 flags,
			 व्योम *cd, u8 cd_count, u32 count);
काष्ठा tidaw *tcw_add_tidaw(काष्ठा tcw *tcw, पूर्णांक num_tidaws, u8 flags,
			    व्योम *addr, u32 count);

#पूर्ण_अगर /* _ASM_S390_FCX_H */
