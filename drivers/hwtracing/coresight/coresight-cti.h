<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018 Linaro Limited, All rights reserved.
 * Author: Mike Leach <mike.leach@linaro.org>
 */

#अगर_अघोषित _CORESIGHT_CORESIGHT_CTI_H
#घोषणा _CORESIGHT_CORESIGHT_CTI_H

#समावेश <linux/coresight.h>
#समावेश <linux/device.h>
#समावेश <linux/fwnode.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>

#समावेश "coresight-priv.h"

/*
 * Device रेजिस्टरs
 * 0x000 - 0x144: CTI programming and status
 * 0xEDC - 0xEF8: CTI पूर्णांकegration test.
 * 0xF00 - 0xFFC: Coresight management रेजिस्टरs.
 */
/* CTI programming रेजिस्टरs */
#घोषणा CTICONTROL		0x000
#घोषणा CTIINTACK		0x010
#घोषणा CTIAPPSET		0x014
#घोषणा CTIAPPCLEAR		0x018
#घोषणा CTIAPPPULSE		0x01C
#घोषणा CTIINEN(n)		(0x020 + (4 * n))
#घोषणा CTIOUTEN(n)		(0x0A0 + (4 * n))
#घोषणा CTITRIGINSTATUS		0x130
#घोषणा CTITRIGOUTSTATUS	0x134
#घोषणा CTICHINSTATUS		0x138
#घोषणा CTICHOUTSTATUS		0x13C
#घोषणा CTIGATE			0x140
#घोषणा ASICCTL			0x144
/* Integration test रेजिस्टरs */
#घोषणा ITCHINACK		0xEDC /* WO CTI CSSoc 400 only*/
#घोषणा ITTRIGINACK		0xEE0 /* WO CTI CSSoc 400 only*/
#घोषणा ITCHOUT			0xEE4 /* WO RW-600 */
#घोषणा ITTRIGOUT		0xEE8 /* WO RW-600 */
#घोषणा ITCHOUTACK		0xEEC /* RO CTI CSSoc 400 only*/
#घोषणा ITTRIGOUTACK		0xEF0 /* RO CTI CSSoc 400 only*/
#घोषणा ITCHIN			0xEF4 /* RO */
#घोषणा ITTRIGIN		0xEF8 /* RO */
/* management रेजिस्टरs */
#घोषणा CTIDEVAFF0		0xFA8
#घोषणा CTIDEVAFF1		0xFAC

/*
 * CTI CSSoc 600 has a max of 32 trigger संकेतs per direction.
 * CTI CSSoc 400 has 8 IO triggers - other CTIs can be impl def.
 * Max of in and out defined in the DEVID रेजिस्टर.
 * - pick up actual number used from .dts parameters अगर present.
 */
#घोषणा CTIINOUTEN_MAX		32

/**
 * Group of related trigger संकेतs
 *
 * @nr_sigs: number of संकेतs in the group.
 * @used_mask: biपंचांगask representing the संकेत indexes in the group.
 * @sig_types: array of types क्रम the संकेतs, length nr_sigs.
 */
काष्ठा cti_trig_grp अणु
	पूर्णांक nr_sigs;
	u32 used_mask;
	पूर्णांक sig_types[];
पूर्ण;

/**
 * Trigger connection - connection between a CTI and other (coresight) device
 * lists input and output trigger संकेतs क्रम the device
 *
 * @con_in: connected CTIIN संकेतs क्रम the device.
 * @con_out: connected CTIOUT संकेतs क्रम the device.
 * @con_dev: coresight device connected to the CTI, शून्य अगर not CS device
 * @con_dev_name: name of connected device (CS or CPU)
 * @node: entry node in list of connections.
 * @con_attrs: Dynamic sysfs attributes specअगरic to this connection.
 * @attr_group: Dynamic attribute group created क्रम this connection.
 */
काष्ठा cti_trig_con अणु
	काष्ठा cti_trig_grp *con_in;
	काष्ठा cti_trig_grp *con_out;
	काष्ठा coresight_device *con_dev;
	स्थिर अक्षर *con_dev_name;
	काष्ठा list_head node;
	काष्ठा attribute **con_attrs;
	काष्ठा attribute_group *attr_group;
पूर्ण;

/**
 * काष्ठा cti_device - description of CTI device properties.
 *
 * @nt_trig_con: Number of बाह्यal devices connected to this device.
 * @cपंचांग_id: which CTM this device is connected to (by शेष it is
 *          assumed there is a single CTM per SoC, ID 0).
 * @trig_cons: list of connections to this device.
 * @cpu: CPU ID अगर associated with CPU, -1 otherwise.
 * @con_groups: combined अटल and dynamic sysfs groups क्रम trigger
 *		connections.
 */
काष्ठा cti_device अणु
	पूर्णांक nr_trig_con;
	u32 cपंचांग_id;
	काष्ठा list_head trig_cons;
	पूर्णांक cpu;
	स्थिर काष्ठा attribute_group **con_groups;
पूर्ण;

/**
 * काष्ठा cti_config - configuration of the CTI device hardware
 *
 * @nr_trig_max: Max number of trigger संकेतs implemented on device.
 *		 (max of trig_in or trig_out) - from ID रेजिस्टर.
 * @nr_cपंचांग_channels: number of available CTM channels - from ID रेजिस्टर.
 * @enable_req_count: CTI is enabled aदीर्घside >=1 associated devices.
 * @hw_enabled: true अगर hw is currently enabled.
 * @hw_घातered: true अगर associated cpu घातered on, or no cpu.
 * @trig_in_use: bitfield of in triggers रेजिस्टरed as in use.
 * @trig_out_use: bitfield of out triggers रेजिस्टरed as in use.
 * @trig_out_filter: bitfield of out triggers that are blocked अगर filter
 *		     enabled. Typically this would be dbgreq / restart on
 *		     a core CTI.
 * @trig_filter_enable: 1 अगर filtering enabled.
 * @xtrig_rchan_sel: channel selection क्रम xtrigger connection show.
 * @ctiappset: CTI Software application channel set.
 * @ctiinout_sel: रेजिस्टर selector क्रम INEN and OUTEN regs.
 * @ctiinen: enable input trigger to a channel.
 * @ctiouten: enable output trigger from a channel.
 * @ctigate: gate channel output from CTI to CTM.
 * @asicctl: asic control रेजिस्टर.
 */
काष्ठा cti_config अणु
	/* hardware description */
	पूर्णांक nr_cपंचांग_channels;
	पूर्णांक nr_trig_max;

	/* cti enable control */
	atomic_t enable_req_count;
	bool hw_enabled;
	bool hw_घातered;

	/* रेजिस्टरed triggers and filtering */
	u32 trig_in_use;
	u32 trig_out_use;
	u32 trig_out_filter;
	bool trig_filter_enable;
	u8 xtrig_rchan_sel;

	/* cti cross trig programmable regs */
	u32 ctiappset;
	u8 ctiinout_sel;
	u32 ctiinen[CTIINOUTEN_MAX];
	u32 ctiouten[CTIINOUTEN_MAX];
	u32 ctigate;
	u32 asicctl;
पूर्ण;

/**
 * काष्ठा cti_drvdata - specअगरics क्रम the CTI device
 * @base:	Memory mapped base address क्रम this component..
 * @csdev:	Standard CoreSight device inक्रमmation.
 * @ctidev:	Extra inक्रमmation needed by the CTI/CTM framework.
 * @spinlock:	Control data access to one at a समय.
 * @config:	Configuration data क्रम this CTI device.
 * @node:	List entry of this device in the list of CTI devices.
 * @csdev_release: release function क्रम underlying coresight_device.
 */
काष्ठा cti_drvdata अणु
	व्योम __iomem *base;
	काष्ठा coresight_device	*csdev;
	काष्ठा cti_device ctidev;
	spinlock_t spinlock;
	काष्ठा cti_config config;
	काष्ठा list_head node;
	व्योम (*csdev_release)(काष्ठा device *dev);
पूर्ण;

/*
 * Channel operation types.
 */
क्रमागत cti_chan_op अणु
	CTI_CHAN_ATTACH,
	CTI_CHAN_DETACH,
पूर्ण;

क्रमागत cti_trig_dir अणु
	CTI_TRIG_IN,
	CTI_TRIG_OUT,
पूर्ण;

क्रमागत cti_chan_gate_op अणु
	CTI_GATE_CHAN_ENABLE,
	CTI_GATE_CHAN_DISABLE,
पूर्ण;

क्रमागत cti_chan_set_op अणु
	CTI_CHAN_SET,
	CTI_CHAN_CLR,
	CTI_CHAN_PULSE,
पूर्ण;

/* निजी cti driver fns & vars */
बाह्य स्थिर काष्ठा attribute_group *coresight_cti_groups[];
पूर्णांक cti_add_शेष_connection(काष्ठा device *dev,
			       काष्ठा cti_drvdata *drvdata);
पूर्णांक cti_add_connection_entry(काष्ठा device *dev, काष्ठा cti_drvdata *drvdata,
			     काष्ठा cti_trig_con *tc,
			     काष्ठा coresight_device *csdev,
			     स्थिर अक्षर *assoc_dev_name);
काष्ठा cti_trig_con *cti_allocate_trig_con(काष्ठा device *dev, पूर्णांक in_sigs,
					   पूर्णांक out_sigs);
पूर्णांक cti_enable(काष्ठा coresight_device *csdev);
पूर्णांक cti_disable(काष्ठा coresight_device *csdev);
व्योम cti_ग_लिखो_all_hw_regs(काष्ठा cti_drvdata *drvdata);
व्योम cti_ग_लिखो_पूर्णांकack(काष्ठा device *dev, u32 ackval);
व्योम cti_ग_लिखो_single_reg(काष्ठा cti_drvdata *drvdata, पूर्णांक offset, u32 value);
पूर्णांक cti_channel_trig_op(काष्ठा device *dev, क्रमागत cti_chan_op op,
			क्रमागत cti_trig_dir direction, u32 channel_idx,
			u32 trigger_idx);
पूर्णांक cti_channel_gate_op(काष्ठा device *dev, क्रमागत cti_chan_gate_op op,
			u32 channel_idx);
पूर्णांक cti_channel_setop(काष्ठा device *dev, क्रमागत cti_chan_set_op op,
		      u32 channel_idx);
पूर्णांक cti_create_cons_sysfs(काष्ठा device *dev, काष्ठा cti_drvdata *drvdata);
काष्ठा coresight_platक्रमm_data *
coresight_cti_get_platक्रमm_data(काष्ठा device *dev);
स्थिर अक्षर *cti_plat_get_node_name(काष्ठा fwnode_handle *fwnode);

/* cti घातered and enabled */
अटल अंतरभूत bool cti_active(काष्ठा cti_config *cfg)
अणु
	वापस cfg->hw_घातered && cfg->hw_enabled;
पूर्ण

#पूर्ण_अगर  /* _CORESIGHT_CORESIGHT_CTI_H */
