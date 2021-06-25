<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2015-2018, Intel Corporation.
 */

#अगर_अघोषित __KCS_BMC_H__
#घोषणा __KCS_BMC_H__

#समावेश <linux/miscdevice.h>

/* Dअगरferent phases of the KCS BMC module.
 *  KCS_PHASE_IDLE:
 *            BMC should not be expecting nor sending any data.
 *  KCS_PHASE_WRITE_START:
 *            BMC is receiving a WRITE_START command from प्रणाली software.
 *  KCS_PHASE_WRITE_DATA:
 *            BMC is receiving a data byte from प्रणाली software.
 *  KCS_PHASE_WRITE_END_CMD:
 *            BMC is रुकोing a last data byte from प्रणाली software.
 *  KCS_PHASE_WRITE_DONE:
 *            BMC has received the whole request from प्रणाली software.
 *  KCS_PHASE_WAIT_READ:
 *            BMC is रुकोing the response from the upper IPMI service.
 *  KCS_PHASE_READ:
 *            BMC is transferring the response to प्रणाली software.
 *  KCS_PHASE_ABORT_ERROR1:
 *            BMC is रुकोing error status request from प्रणाली software.
 *  KCS_PHASE_ABORT_ERROR2:
 *            BMC is रुकोing क्रम idle status afer error from प्रणाली software.
 *  KCS_PHASE_ERROR:
 *            BMC has detected a protocol violation at the पूर्णांकerface level.
 */
क्रमागत kcs_phases अणु
	KCS_PHASE_IDLE,

	KCS_PHASE_WRITE_START,
	KCS_PHASE_WRITE_DATA,
	KCS_PHASE_WRITE_END_CMD,
	KCS_PHASE_WRITE_DONE,

	KCS_PHASE_WAIT_READ,
	KCS_PHASE_READ,

	KCS_PHASE_ABORT_ERROR1,
	KCS_PHASE_ABORT_ERROR2,
	KCS_PHASE_ERROR
पूर्ण;

/* IPMI 2.0 - Table 9-4, KCS Interface Status Codes */
क्रमागत kcs_errors अणु
	KCS_NO_ERROR                = 0x00,
	KCS_ABORTED_BY_COMMAND      = 0x01,
	KCS_ILLEGAL_CONTROL_CODE    = 0x02,
	KCS_LENGTH_ERROR            = 0x06,
	KCS_UNSPECIFIED_ERROR       = 0xFF
पूर्ण;

/* IPMI 2.0 - 9.5, KCS Interface Registers
 * @idr: Input Data Register
 * @odr: Output Data Register
 * @str: Status Register
 */
काष्ठा kcs_ioreg अणु
	u32 idr;
	u32 odr;
	u32 str;
पूर्ण;

काष्ठा kcs_bmc अणु
	spinlock_t lock;

	u32 channel;
	पूर्णांक running;

	/* Setup by BMC KCS controller driver */
	काष्ठा kcs_ioreg ioreg;
	u8 (*io_inputb)(काष्ठा kcs_bmc *kcs_bmc, u32 reg);
	व्योम (*io_outputb)(काष्ठा kcs_bmc *kcs_bmc, u32 reg, u8 b);

	क्रमागत kcs_phases phase;
	क्रमागत kcs_errors error;

	रुको_queue_head_t queue;
	bool data_in_avail;
	पूर्णांक  data_in_idx;
	u8  *data_in;

	पूर्णांक  data_out_idx;
	पूर्णांक  data_out_len;
	u8  *data_out;

	काष्ठा mutex mutex;
	u8 *kbuffer;

	काष्ठा miscdevice miscdev;

	अचिन्हित दीर्घ priv[];
पूर्ण;

अटल अंतरभूत व्योम *kcs_bmc_priv(काष्ठा kcs_bmc *kcs_bmc)
अणु
	वापस kcs_bmc->priv;
पूर्ण

पूर्णांक kcs_bmc_handle_event(काष्ठा kcs_bmc *kcs_bmc);
काष्ठा kcs_bmc *kcs_bmc_alloc(काष्ठा device *dev, पूर्णांक माप_priv,
					u32 channel);
#पूर्ण_अगर /* __KCS_BMC_H__ */
