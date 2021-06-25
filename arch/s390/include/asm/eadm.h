<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_EADM_H
#घोषणा _ASM_S390_EADM_H

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/blk_types.h>

काष्ठा arqb अणु
	u64 data;
	u16 fmt:4;
	u16:12;
	u16 cmd_code;
	u16:16;
	u16 msb_count;
	u32 reserved[12];
पूर्ण __packed;

#घोषणा ARQB_CMD_MOVE	1

काष्ठा arsb अणु
	u16 fmt:4;
	u32:28;
	u8 ef;
	u8:8;
	u8 ecbi;
	u8:8;
	u8 fvf;
	u16:16;
	u8 eqc;
	u32:32;
	u64 fail_msb;
	u64 fail_aidaw;
	u64 fail_ms;
	u64 fail_scm;
	u32 reserved[4];
पूर्ण __packed;

#घोषणा EQC_WR_PROHIBIT 22

काष्ठा msb अणु
	u8 fmt:4;
	u8 oc:4;
	u8 flags;
	u16:12;
	u16 bs:4;
	u32 blk_count;
	u64 data_addr;
	u64 scm_addr;
	u64:64;
पूर्ण __packed;

काष्ठा aidaw अणु
	u8 flags;
	u32 :24;
	u32 :32;
	u64 data_addr;
पूर्ण __packed;

#घोषणा MSB_OC_CLEAR	0
#घोषणा MSB_OC_READ	1
#घोषणा MSB_OC_WRITE	2
#घोषणा MSB_OC_RELEASE	3

#घोषणा MSB_FLAG_BNM	0x80
#घोषणा MSB_FLAG_IDA	0x40

#घोषणा MSB_BS_4K	0
#घोषणा MSB_BS_1M	1

#घोषणा AOB_NR_MSB	124

काष्ठा aob अणु
	काष्ठा arqb request;
	काष्ठा arsb response;
	काष्ठा msb msb[AOB_NR_MSB];
पूर्ण __packed __aligned(PAGE_SIZE);

काष्ठा aob_rq_header अणु
	काष्ठा scm_device *scmdev;
	अक्षर data[0];
पूर्ण;

काष्ठा scm_device अणु
	u64 address;
	u64 size;
	अचिन्हित पूर्णांक nr_max_block;
	काष्ठा device dev;
	काष्ठा अणु
		अचिन्हित पूर्णांक persistence:4;
		अचिन्हित पूर्णांक oper_state:4;
		अचिन्हित पूर्णांक data_state:4;
		अचिन्हित पूर्णांक rank:4;
		अचिन्हित पूर्णांक release:1;
		अचिन्हित पूर्णांक res_id:8;
	पूर्ण __packed attrs;
पूर्ण;

#घोषणा OP_STATE_GOOD		1
#घोषणा OP_STATE_TEMP_ERR	2
#घोषणा OP_STATE_PERM_ERR	3

क्रमागत scm_event अणुSCM_CHANGE, SCM_AVAILपूर्ण;

काष्ठा scm_driver अणु
	काष्ठा device_driver drv;
	पूर्णांक (*probe) (काष्ठा scm_device *scmdev);
	पूर्णांक (*हटाओ) (काष्ठा scm_device *scmdev);
	व्योम (*notअगरy) (काष्ठा scm_device *scmdev, क्रमागत scm_event event);
	व्योम (*handler) (काष्ठा scm_device *scmdev, व्योम *data,
			blk_status_t error);
पूर्ण;

पूर्णांक scm_driver_रेजिस्टर(काष्ठा scm_driver *scmdrv);
व्योम scm_driver_unरेजिस्टर(काष्ठा scm_driver *scmdrv);

पूर्णांक eadm_start_aob(काष्ठा aob *aob);
व्योम scm_irq_handler(काष्ठा aob *aob, blk_status_t error);

#पूर्ण_अगर /* _ASM_S390_EADM_H */
