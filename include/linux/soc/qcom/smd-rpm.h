<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __QCOM_SMD_RPM_H__
#घोषणा __QCOM_SMD_RPM_H__

काष्ठा qcom_smd_rpm;

#घोषणा QCOM_SMD_RPM_ACTIVE_STATE        0
#घोषणा QCOM_SMD_RPM_SLEEP_STATE         1

/*
 * Constants used क्रम addressing resources in the RPM.
 */
#घोषणा QCOM_SMD_RPM_BBYB	0x62796262
#घोषणा QCOM_SMD_RPM_BOBB	0x62626f62
#घोषणा QCOM_SMD_RPM_BOOST	0x61747362
#घोषणा QCOM_SMD_RPM_BUS_CLK	0x316b6c63
#घोषणा QCOM_SMD_RPM_BUS_MASTER	0x73616d62
#घोषणा QCOM_SMD_RPM_BUS_SLAVE	0x766c7362
#घोषणा QCOM_SMD_RPM_CLK_BUF_A	0x616B6C63
#घोषणा QCOM_SMD_RPM_LDOA	0x616f646c
#घोषणा QCOM_SMD_RPM_LDOB	0x626F646C
#घोषणा QCOM_SMD_RPM_RWCX	0x78637772
#घोषणा QCOM_SMD_RPM_RWMX	0x786d7772
#घोषणा QCOM_SMD_RPM_RWLC	0x636c7772
#घोषणा QCOM_SMD_RPM_RWLM	0x6d6c7772
#घोषणा QCOM_SMD_RPM_MEM_CLK	0x326b6c63
#घोषणा QCOM_SMD_RPM_MISC_CLK	0x306b6c63
#घोषणा QCOM_SMD_RPM_NCPA	0x6170636E
#घोषणा QCOM_SMD_RPM_NCPB	0x6270636E
#घोषणा QCOM_SMD_RPM_OCMEM_PWR	0x706d636f
#घोषणा QCOM_SMD_RPM_QPIC_CLK	0x63697071
#घोषणा QCOM_SMD_RPM_SMPA	0x61706d73
#घोषणा QCOM_SMD_RPM_SMPB	0x62706d73
#घोषणा QCOM_SMD_RPM_SPDM	0x63707362
#घोषणा QCOM_SMD_RPM_VSA	0x00617376
#घोषणा QCOM_SMD_RPM_MMAXI_CLK	0x69786d6d
#घोषणा QCOM_SMD_RPM_IPA_CLK	0x617069
#घोषणा QCOM_SMD_RPM_CE_CLK	0x6563
#घोषणा QCOM_SMD_RPM_AGGR_CLK	0x72676761

पूर्णांक qcom_rpm_smd_ग_लिखो(काष्ठा qcom_smd_rpm *rpm,
		       पूर्णांक state,
		       u32 resource_type, u32 resource_id,
		       व्योम *buf, माप_प्रकार count);

#पूर्ण_अगर
