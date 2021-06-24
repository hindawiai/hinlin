<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Helper functions क्रम scsw access.
 *
 *    Copyright IBM Corp. 2008, 2012
 *    Author(s): Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#अगर_अघोषित _ASM_S390_SCSW_H_
#घोषणा _ASM_S390_SCSW_H_

#समावेश <linux/types.h>
#समावेश <यंत्र/css_अक्षरs.h>
#समावेश <यंत्र/cपन.स>

/**
 * काष्ठा cmd_scsw - command-mode subchannel status word
 * @key: subchannel key
 * @sctl: suspend control
 * @eswf: esw क्रमmat
 * @cc: deferred condition code
 * @fmt: क्रमmat
 * @pfch: prefetch
 * @isic: initial-status पूर्णांकerruption control
 * @alcc: address-limit checking control
 * @ssi: suppress-suspended पूर्णांकerruption
 * @zcc: zero condition code
 * @ectl: extended control
 * @pno: path not operational
 * @res: reserved
 * @fctl: function control
 * @actl: activity control
 * @stctl: status control
 * @cpa: channel program address
 * @dstat: device status
 * @cstat: subchannel status
 * @count: residual count
 */
काष्ठा cmd_scsw अणु
	__u32 key  : 4;
	__u32 sctl : 1;
	__u32 eswf : 1;
	__u32 cc   : 2;
	__u32 fmt  : 1;
	__u32 pfch : 1;
	__u32 isic : 1;
	__u32 alcc : 1;
	__u32 ssi  : 1;
	__u32 zcc  : 1;
	__u32 ectl : 1;
	__u32 pno  : 1;
	__u32 res  : 1;
	__u32 fctl : 3;
	__u32 actl : 7;
	__u32 stctl : 5;
	__u32 cpa;
	__u32 dstat : 8;
	__u32 cstat : 8;
	__u32 count : 16;
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा पंचांग_scsw - transport-mode subchannel status word
 * @key: subchannel key
 * @eswf: esw क्रमmat
 * @cc: deferred condition code
 * @fmt: क्रमmat
 * @x: IRB-क्रमmat control
 * @q: पूर्णांकerrogate-complete
 * @ectl: extended control
 * @pno: path not operational
 * @fctl: function control
 * @actl: activity control
 * @stctl: status control
 * @tcw: TCW address
 * @dstat: device status
 * @cstat: subchannel status
 * @fcxs: FCX status
 * @schxs: subchannel-extended status
 */
काष्ठा पंचांग_scsw अणु
	u32 key:4;
	u32 :1;
	u32 eswf:1;
	u32 cc:2;
	u32 fmt:3;
	u32 x:1;
	u32 q:1;
	u32 :1;
	u32 ectl:1;
	u32 pno:1;
	u32 :1;
	u32 fctl:3;
	u32 actl:7;
	u32 stctl:5;
	u32 tcw;
	u32 dstat:8;
	u32 cstat:8;
	u32 fcxs:8;
	u32 अगरob:1;
	u32 sesq:7;
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा eadm_scsw - subchannel status word क्रम eadm subchannels
 * @key: subchannel key
 * @eswf: esw क्रमmat
 * @cc: deferred condition code
 * @ectl: extended control
 * @fctl: function control
 * @actl: activity control
 * @stctl: status control
 * @aob: AOB address
 * @dstat: device status
 * @cstat: subchannel status
 */
काष्ठा eadm_scsw अणु
	u32 key:4;
	u32:1;
	u32 eswf:1;
	u32 cc:2;
	u32:6;
	u32 ectl:1;
	u32:2;
	u32 fctl:3;
	u32 actl:7;
	u32 stctl:5;
	u32 aob;
	u32 dstat:8;
	u32 cstat:8;
	u32:16;
पूर्ण __packed;

/**
 * जोड़ scsw - subchannel status word
 * @cmd: command-mode SCSW
 * @पंचांग: transport-mode SCSW
 * @eadm: eadm SCSW
 */
जोड़ scsw अणु
	काष्ठा cmd_scsw cmd;
	काष्ठा पंचांग_scsw पंचांग;
	काष्ठा eadm_scsw eadm;
पूर्ण __packed;

#घोषणा SCSW_FCTL_CLEAR_FUNC	 0x1
#घोषणा SCSW_FCTL_HALT_FUNC	 0x2
#घोषणा SCSW_FCTL_START_FUNC	 0x4

#घोषणा SCSW_ACTL_SUSPENDED	 0x1
#घोषणा SCSW_ACTL_DEVACT	 0x2
#घोषणा SCSW_ACTL_SCHACT	 0x4
#घोषणा SCSW_ACTL_CLEAR_PEND	 0x8
#घोषणा SCSW_ACTL_HALT_PEND	 0x10
#घोषणा SCSW_ACTL_START_PEND	 0x20
#घोषणा SCSW_ACTL_RESUME_PEND	 0x40

#घोषणा SCSW_STCTL_STATUS_PEND	 0x1
#घोषणा SCSW_STCTL_SEC_STATUS	 0x2
#घोषणा SCSW_STCTL_PRIM_STATUS	 0x4
#घोषणा SCSW_STCTL_INTER_STATUS	 0x8
#घोषणा SCSW_STCTL_ALERT_STATUS	 0x10

#घोषणा DEV_STAT_ATTENTION	 0x80
#घोषणा DEV_STAT_STAT_MOD	 0x40
#घोषणा DEV_STAT_CU_END		 0x20
#घोषणा DEV_STAT_BUSY		 0x10
#घोषणा DEV_STAT_CHN_END	 0x08
#घोषणा DEV_STAT_DEV_END	 0x04
#घोषणा DEV_STAT_UNIT_CHECK	 0x02
#घोषणा DEV_STAT_UNIT_EXCEP	 0x01

#घोषणा SCHN_STAT_PCI		 0x80
#घोषणा SCHN_STAT_INCORR_LEN	 0x40
#घोषणा SCHN_STAT_PROG_CHECK	 0x20
#घोषणा SCHN_STAT_PROT_CHECK	 0x10
#घोषणा SCHN_STAT_CHN_DATA_CHK	 0x08
#घोषणा SCHN_STAT_CHN_CTRL_CHK	 0x04
#घोषणा SCHN_STAT_INTF_CTRL_CHK	 0x02
#घोषणा SCHN_STAT_CHAIN_CHECK	 0x01

#घोषणा SCSW_SESQ_DEV_NOFCX	 3
#घोषणा SCSW_SESQ_PATH_NOFCX	 4

/*
 * architectured values क्रम first sense byte
 */
#घोषणा SNS0_CMD_REJECT		0x80
#घोषणा SNS_CMD_REJECT		SNS0_CMD_REJEC
#घोषणा SNS0_INTERVENTION_REQ	0x40
#घोषणा SNS0_BUS_OUT_CHECK	0x20
#घोषणा SNS0_EQUIPMENT_CHECK	0x10
#घोषणा SNS0_DATA_CHECK		0x08
#घोषणा SNS0_OVERRUN		0x04
#घोषणा SNS0_INCOMPL_DOMAIN	0x01

/*
 * architectured values क्रम second sense byte
 */
#घोषणा SNS1_PERM_ERR		0x80
#घोषणा SNS1_INV_TRACK_FORMAT	0x40
#घोषणा SNS1_EOC		0x20
#घोषणा SNS1_MESSAGE_TO_OPER	0x10
#घोषणा SNS1_NO_REC_FOUND	0x08
#घोषणा SNS1_खाता_PROTECTED	0x04
#घोषणा SNS1_WRITE_INHIBITED	0x02
#घोषणा SNS1_INPRECISE_END	0x01

/*
 * architectured values क्रम third sense byte
 */
#घोषणा SNS2_REQ_INH_WRITE	0x80
#घोषणा SNS2_CORRECTABLE	0x40
#घोषणा SNS2_FIRST_LOG_ERR	0x20
#घोषणा SNS2_ENV_DATA_PRESENT	0x10
#घोषणा SNS2_INPRECISE_END	0x04

/**
 * scsw_is_पंचांग - check क्रम transport mode scsw
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the specअगरied scsw is a transport mode scsw, zero
 * otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_is_पंचांग(जोड़ scsw *scsw)
अणु
	वापस css_general_अक्षरacteristics.fcx && (scsw->पंचांग.x == 1);
पूर्ण

/**
 * scsw_key - वापस scsw key field
 * @scsw: poपूर्णांकer to scsw
 *
 * Return the value of the key field of the specअगरied scsw, regardless of
 * whether it is a transport mode or command mode scsw.
 */
अटल अंतरभूत u32 scsw_key(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw->पंचांग.key;
	अन्यथा
		वापस scsw->cmd.key;
पूर्ण

/**
 * scsw_eswf - वापस scsw eswf field
 * @scsw: poपूर्णांकer to scsw
 *
 * Return the value of the eswf field of the specअगरied scsw, regardless of
 * whether it is a transport mode or command mode scsw.
 */
अटल अंतरभूत u32 scsw_eswf(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw->पंचांग.eswf;
	अन्यथा
		वापस scsw->cmd.eswf;
पूर्ण

/**
 * scsw_cc - वापस scsw cc field
 * @scsw: poपूर्णांकer to scsw
 *
 * Return the value of the cc field of the specअगरied scsw, regardless of
 * whether it is a transport mode or command mode scsw.
 */
अटल अंतरभूत u32 scsw_cc(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw->पंचांग.cc;
	अन्यथा
		वापस scsw->cmd.cc;
पूर्ण

/**
 * scsw_ectl - वापस scsw ectl field
 * @scsw: poपूर्णांकer to scsw
 *
 * Return the value of the ectl field of the specअगरied scsw, regardless of
 * whether it is a transport mode or command mode scsw.
 */
अटल अंतरभूत u32 scsw_ectl(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw->पंचांग.ectl;
	अन्यथा
		वापस scsw->cmd.ectl;
पूर्ण

/**
 * scsw_pno - वापस scsw pno field
 * @scsw: poपूर्णांकer to scsw
 *
 * Return the value of the pno field of the specअगरied scsw, regardless of
 * whether it is a transport mode or command mode scsw.
 */
अटल अंतरभूत u32 scsw_pno(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw->पंचांग.pno;
	अन्यथा
		वापस scsw->cmd.pno;
पूर्ण

/**
 * scsw_fctl - वापस scsw fctl field
 * @scsw: poपूर्णांकer to scsw
 *
 * Return the value of the fctl field of the specअगरied scsw, regardless of
 * whether it is a transport mode or command mode scsw.
 */
अटल अंतरभूत u32 scsw_fctl(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw->पंचांग.fctl;
	अन्यथा
		वापस scsw->cmd.fctl;
पूर्ण

/**
 * scsw_actl - वापस scsw actl field
 * @scsw: poपूर्णांकer to scsw
 *
 * Return the value of the actl field of the specअगरied scsw, regardless of
 * whether it is a transport mode or command mode scsw.
 */
अटल अंतरभूत u32 scsw_actl(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw->पंचांग.actl;
	अन्यथा
		वापस scsw->cmd.actl;
पूर्ण

/**
 * scsw_stctl - वापस scsw stctl field
 * @scsw: poपूर्णांकer to scsw
 *
 * Return the value of the stctl field of the specअगरied scsw, regardless of
 * whether it is a transport mode or command mode scsw.
 */
अटल अंतरभूत u32 scsw_stctl(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw->पंचांग.stctl;
	अन्यथा
		वापस scsw->cmd.stctl;
पूर्ण

/**
 * scsw_dstat - वापस scsw dstat field
 * @scsw: poपूर्णांकer to scsw
 *
 * Return the value of the dstat field of the specअगरied scsw, regardless of
 * whether it is a transport mode or command mode scsw.
 */
अटल अंतरभूत u32 scsw_dstat(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw->पंचांग.dstat;
	अन्यथा
		वापस scsw->cmd.dstat;
पूर्ण

/**
 * scsw_cstat - वापस scsw cstat field
 * @scsw: poपूर्णांकer to scsw
 *
 * Return the value of the cstat field of the specअगरied scsw, regardless of
 * whether it is a transport mode or command mode scsw.
 */
अटल अंतरभूत u32 scsw_cstat(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw->पंचांग.cstat;
	अन्यथा
		वापस scsw->cmd.cstat;
पूर्ण

/**
 * scsw_cmd_is_valid_key - check key field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the key field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_key(जोड़ scsw *scsw)
अणु
	वापस (scsw->cmd.fctl & SCSW_FCTL_START_FUNC);
पूर्ण

/**
 * scsw_cmd_is_valid_sctl - check sctl field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the sctl field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_sctl(जोड़ scsw *scsw)
अणु
	वापस (scsw->cmd.fctl & SCSW_FCTL_START_FUNC);
पूर्ण

/**
 * scsw_cmd_is_valid_eswf - check eswf field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the eswf field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_eswf(जोड़ scsw *scsw)
अणु
	वापस (scsw->cmd.stctl & SCSW_STCTL_STATUS_PEND);
पूर्ण

/**
 * scsw_cmd_is_valid_cc - check cc field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the cc field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_cc(जोड़ scsw *scsw)
अणु
	वापस (scsw->cmd.fctl & SCSW_FCTL_START_FUNC) &&
	       (scsw->cmd.stctl & SCSW_STCTL_STATUS_PEND);
पूर्ण

/**
 * scsw_cmd_is_valid_fmt - check fmt field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the fmt field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_fmt(जोड़ scsw *scsw)
अणु
	वापस (scsw->cmd.fctl & SCSW_FCTL_START_FUNC);
पूर्ण

/**
 * scsw_cmd_is_valid_pfch - check pfch field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the pfch field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_pfch(जोड़ scsw *scsw)
अणु
	वापस (scsw->cmd.fctl & SCSW_FCTL_START_FUNC);
पूर्ण

/**
 * scsw_cmd_is_valid_isic - check isic field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the isic field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_isic(जोड़ scsw *scsw)
अणु
	वापस (scsw->cmd.fctl & SCSW_FCTL_START_FUNC);
पूर्ण

/**
 * scsw_cmd_is_valid_alcc - check alcc field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the alcc field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_alcc(जोड़ scsw *scsw)
अणु
	वापस (scsw->cmd.fctl & SCSW_FCTL_START_FUNC);
पूर्ण

/**
 * scsw_cmd_is_valid_ssi - check ssi field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the ssi field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_ssi(जोड़ scsw *scsw)
अणु
	वापस (scsw->cmd.fctl & SCSW_FCTL_START_FUNC);
पूर्ण

/**
 * scsw_cmd_is_valid_zcc - check zcc field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the zcc field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_zcc(जोड़ scsw *scsw)
अणु
	वापस (scsw->cmd.fctl & SCSW_FCTL_START_FUNC) &&
	       (scsw->cmd.stctl & SCSW_STCTL_INTER_STATUS);
पूर्ण

/**
 * scsw_cmd_is_valid_ectl - check ectl field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the ectl field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_ectl(जोड़ scsw *scsw)
अणु
	वापस (scsw->cmd.stctl & SCSW_STCTL_STATUS_PEND) &&
	       !(scsw->cmd.stctl & SCSW_STCTL_INTER_STATUS) &&
	       (scsw->cmd.stctl & SCSW_STCTL_ALERT_STATUS);
पूर्ण

/**
 * scsw_cmd_is_valid_pno - check pno field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the pno field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_pno(जोड़ scsw *scsw)
अणु
	वापस (scsw->cmd.fctl != 0) &&
	       (scsw->cmd.stctl & SCSW_STCTL_STATUS_PEND) &&
	       (!(scsw->cmd.stctl & SCSW_STCTL_INTER_STATUS) ||
		  (scsw->cmd.actl & SCSW_ACTL_SUSPENDED));
पूर्ण

/**
 * scsw_cmd_is_valid_fctl - check fctl field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the fctl field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_fctl(जोड़ scsw *scsw)
अणु
	/* Only valid अगर pmcw.dnv == 1*/
	वापस 1;
पूर्ण

/**
 * scsw_cmd_is_valid_actl - check actl field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the actl field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_actl(जोड़ scsw *scsw)
अणु
	/* Only valid अगर pmcw.dnv == 1*/
	वापस 1;
पूर्ण

/**
 * scsw_cmd_is_valid_stctl - check stctl field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the stctl field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_stctl(जोड़ scsw *scsw)
अणु
	/* Only valid अगर pmcw.dnv == 1*/
	वापस 1;
पूर्ण

/**
 * scsw_cmd_is_valid_dstat - check dstat field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the dstat field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_dstat(जोड़ scsw *scsw)
अणु
	वापस (scsw->cmd.stctl & SCSW_STCTL_STATUS_PEND) &&
	       (scsw->cmd.cc != 3);
पूर्ण

/**
 * scsw_cmd_is_valid_cstat - check cstat field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the cstat field of the specअगरied command mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_valid_cstat(जोड़ scsw *scsw)
अणु
	वापस (scsw->cmd.stctl & SCSW_STCTL_STATUS_PEND) &&
	       (scsw->cmd.cc != 3);
पूर्ण

/**
 * scsw_पंचांग_is_valid_key - check key field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the key field of the specअगरied transport mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_valid_key(जोड़ scsw *scsw)
अणु
	वापस (scsw->पंचांग.fctl & SCSW_FCTL_START_FUNC);
पूर्ण

/**
 * scsw_पंचांग_is_valid_eswf - check eswf field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the eswf field of the specअगरied transport mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_valid_eswf(जोड़ scsw *scsw)
अणु
	वापस (scsw->पंचांग.stctl & SCSW_STCTL_STATUS_PEND);
पूर्ण

/**
 * scsw_पंचांग_is_valid_cc - check cc field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the cc field of the specअगरied transport mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_valid_cc(जोड़ scsw *scsw)
अणु
	वापस (scsw->पंचांग.fctl & SCSW_FCTL_START_FUNC) &&
	       (scsw->पंचांग.stctl & SCSW_STCTL_STATUS_PEND);
पूर्ण

/**
 * scsw_पंचांग_is_valid_fmt - check fmt field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the fmt field of the specअगरied transport mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_valid_fmt(जोड़ scsw *scsw)
अणु
	वापस 1;
पूर्ण

/**
 * scsw_पंचांग_is_valid_x - check x field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the x field of the specअगरied transport mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_valid_x(जोड़ scsw *scsw)
अणु
	वापस 1;
पूर्ण

/**
 * scsw_पंचांग_is_valid_q - check q field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the q field of the specअगरied transport mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_valid_q(जोड़ scsw *scsw)
अणु
	वापस 1;
पूर्ण

/**
 * scsw_पंचांग_is_valid_ectl - check ectl field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the ectl field of the specअगरied transport mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_valid_ectl(जोड़ scsw *scsw)
अणु
	वापस (scsw->पंचांग.stctl & SCSW_STCTL_STATUS_PEND) &&
	       !(scsw->पंचांग.stctl & SCSW_STCTL_INTER_STATUS) &&
	       (scsw->पंचांग.stctl & SCSW_STCTL_ALERT_STATUS);
पूर्ण

/**
 * scsw_पंचांग_is_valid_pno - check pno field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the pno field of the specअगरied transport mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_valid_pno(जोड़ scsw *scsw)
अणु
	वापस (scsw->पंचांग.fctl != 0) &&
	       (scsw->पंचांग.stctl & SCSW_STCTL_STATUS_PEND) &&
	       (!(scsw->पंचांग.stctl & SCSW_STCTL_INTER_STATUS) ||
		 ((scsw->पंचांग.stctl & SCSW_STCTL_INTER_STATUS) &&
		  (scsw->पंचांग.actl & SCSW_ACTL_SUSPENDED)));
पूर्ण

/**
 * scsw_पंचांग_is_valid_fctl - check fctl field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the fctl field of the specअगरied transport mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_valid_fctl(जोड़ scsw *scsw)
अणु
	/* Only valid अगर pmcw.dnv == 1*/
	वापस 1;
पूर्ण

/**
 * scsw_पंचांग_is_valid_actl - check actl field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the actl field of the specअगरied transport mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_valid_actl(जोड़ scsw *scsw)
अणु
	/* Only valid अगर pmcw.dnv == 1*/
	वापस 1;
पूर्ण

/**
 * scsw_पंचांग_is_valid_stctl - check stctl field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the stctl field of the specअगरied transport mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_valid_stctl(जोड़ scsw *scsw)
अणु
	/* Only valid अगर pmcw.dnv == 1*/
	वापस 1;
पूर्ण

/**
 * scsw_पंचांग_is_valid_dstat - check dstat field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the dstat field of the specअगरied transport mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_valid_dstat(जोड़ scsw *scsw)
अणु
	वापस (scsw->पंचांग.stctl & SCSW_STCTL_STATUS_PEND) &&
	       (scsw->पंचांग.cc != 3);
पूर्ण

/**
 * scsw_पंचांग_is_valid_cstat - check cstat field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the cstat field of the specअगरied transport mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_valid_cstat(जोड़ scsw *scsw)
अणु
	वापस (scsw->पंचांग.stctl & SCSW_STCTL_STATUS_PEND) &&
	       (scsw->पंचांग.cc != 3);
पूर्ण

/**
 * scsw_पंचांग_is_valid_fcxs - check fcxs field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the fcxs field of the specअगरied transport mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_valid_fcxs(जोड़ scsw *scsw)
अणु
	वापस 1;
पूर्ण

/**
 * scsw_पंचांग_is_valid_schxs - check schxs field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the schxs field of the specअगरied transport mode scsw is
 * valid, zero otherwise.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_valid_schxs(जोड़ scsw *scsw)
अणु
	वापस (scsw->पंचांग.cstat & (SCHN_STAT_PROG_CHECK |
				  SCHN_STAT_INTF_CTRL_CHK |
				  SCHN_STAT_PROT_CHECK |
				  SCHN_STAT_CHN_DATA_CHK));
पूर्ण

/**
 * scsw_is_valid_actl - check actl field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the actl field of the specअगरied scsw is valid,
 * regardless of whether it is a transport mode or command mode scsw.
 * Return zero अगर the field करोes not contain a valid value.
 */
अटल अंतरभूत पूर्णांक scsw_is_valid_actl(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw_पंचांग_is_valid_actl(scsw);
	अन्यथा
		वापस scsw_cmd_is_valid_actl(scsw);
पूर्ण

/**
 * scsw_is_valid_cc - check cc field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the cc field of the specअगरied scsw is valid,
 * regardless of whether it is a transport mode or command mode scsw.
 * Return zero अगर the field करोes not contain a valid value.
 */
अटल अंतरभूत पूर्णांक scsw_is_valid_cc(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw_पंचांग_is_valid_cc(scsw);
	अन्यथा
		वापस scsw_cmd_is_valid_cc(scsw);
पूर्ण

/**
 * scsw_is_valid_cstat - check cstat field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the cstat field of the specअगरied scsw is valid,
 * regardless of whether it is a transport mode or command mode scsw.
 * Return zero अगर the field करोes not contain a valid value.
 */
अटल अंतरभूत पूर्णांक scsw_is_valid_cstat(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw_पंचांग_is_valid_cstat(scsw);
	अन्यथा
		वापस scsw_cmd_is_valid_cstat(scsw);
पूर्ण

/**
 * scsw_is_valid_dstat - check dstat field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the dstat field of the specअगरied scsw is valid,
 * regardless of whether it is a transport mode or command mode scsw.
 * Return zero अगर the field करोes not contain a valid value.
 */
अटल अंतरभूत पूर्णांक scsw_is_valid_dstat(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw_पंचांग_is_valid_dstat(scsw);
	अन्यथा
		वापस scsw_cmd_is_valid_dstat(scsw);
पूर्ण

/**
 * scsw_is_valid_ectl - check ectl field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the ectl field of the specअगरied scsw is valid,
 * regardless of whether it is a transport mode or command mode scsw.
 * Return zero अगर the field करोes not contain a valid value.
 */
अटल अंतरभूत पूर्णांक scsw_is_valid_ectl(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw_पंचांग_is_valid_ectl(scsw);
	अन्यथा
		वापस scsw_cmd_is_valid_ectl(scsw);
पूर्ण

/**
 * scsw_is_valid_eswf - check eswf field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the eswf field of the specअगरied scsw is valid,
 * regardless of whether it is a transport mode or command mode scsw.
 * Return zero अगर the field करोes not contain a valid value.
 */
अटल अंतरभूत पूर्णांक scsw_is_valid_eswf(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw_पंचांग_is_valid_eswf(scsw);
	अन्यथा
		वापस scsw_cmd_is_valid_eswf(scsw);
पूर्ण

/**
 * scsw_is_valid_fctl - check fctl field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the fctl field of the specअगरied scsw is valid,
 * regardless of whether it is a transport mode or command mode scsw.
 * Return zero अगर the field करोes not contain a valid value.
 */
अटल अंतरभूत पूर्णांक scsw_is_valid_fctl(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw_पंचांग_is_valid_fctl(scsw);
	अन्यथा
		वापस scsw_cmd_is_valid_fctl(scsw);
पूर्ण

/**
 * scsw_is_valid_key - check key field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the key field of the specअगरied scsw is valid,
 * regardless of whether it is a transport mode or command mode scsw.
 * Return zero अगर the field करोes not contain a valid value.
 */
अटल अंतरभूत पूर्णांक scsw_is_valid_key(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw_पंचांग_is_valid_key(scsw);
	अन्यथा
		वापस scsw_cmd_is_valid_key(scsw);
पूर्ण

/**
 * scsw_is_valid_pno - check pno field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the pno field of the specअगरied scsw is valid,
 * regardless of whether it is a transport mode or command mode scsw.
 * Return zero अगर the field करोes not contain a valid value.
 */
अटल अंतरभूत पूर्णांक scsw_is_valid_pno(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw_पंचांग_is_valid_pno(scsw);
	अन्यथा
		वापस scsw_cmd_is_valid_pno(scsw);
पूर्ण

/**
 * scsw_is_valid_stctl - check stctl field validity
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the stctl field of the specअगरied scsw is valid,
 * regardless of whether it is a transport mode or command mode scsw.
 * Return zero अगर the field करोes not contain a valid value.
 */
अटल अंतरभूत पूर्णांक scsw_is_valid_stctl(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw_पंचांग_is_valid_stctl(scsw);
	अन्यथा
		वापस scsw_cmd_is_valid_stctl(scsw);
पूर्ण

/**
 * scsw_cmd_is_solicited - check क्रम solicited scsw
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the command mode scsw indicates that the associated
 * status condition is solicited, zero अगर it is unsolicited.
 */
अटल अंतरभूत पूर्णांक scsw_cmd_is_solicited(जोड़ scsw *scsw)
अणु
	वापस (scsw->cmd.cc != 0) || (scsw->cmd.stctl !=
		(SCSW_STCTL_STATUS_PEND | SCSW_STCTL_ALERT_STATUS));
पूर्ण

/**
 * scsw_पंचांग_is_solicited - check क्रम solicited scsw
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the transport mode scsw indicates that the associated
 * status condition is solicited, zero अगर it is unsolicited.
 */
अटल अंतरभूत पूर्णांक scsw_पंचांग_is_solicited(जोड़ scsw *scsw)
अणु
	वापस (scsw->पंचांग.cc != 0) || (scsw->पंचांग.stctl !=
		(SCSW_STCTL_STATUS_PEND | SCSW_STCTL_ALERT_STATUS));
पूर्ण

/**
 * scsw_is_solicited - check क्रम solicited scsw
 * @scsw: poपूर्णांकer to scsw
 *
 * Return non-zero अगर the transport or command mode scsw indicates that the
 * associated status condition is solicited, zero अगर it is unsolicited.
 */
अटल अंतरभूत पूर्णांक scsw_is_solicited(जोड़ scsw *scsw)
अणु
	अगर (scsw_is_पंचांग(scsw))
		वापस scsw_पंचांग_is_solicited(scsw);
	अन्यथा
		वापस scsw_cmd_is_solicited(scsw);
पूर्ण

#पूर्ण_अगर /* _ASM_S390_SCSW_H_ */
