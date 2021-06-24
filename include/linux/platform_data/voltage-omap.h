<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP Voltage Management Routines
 *
 * Copyright (C) 2011, Texas Instruments, Inc.
 */

#अगर_अघोषित __ARCH_ARM_OMAP_VOLTAGE_H
#घोषणा __ARCH_ARM_OMAP_VOLTAGE_H

/**
 * काष्ठा omap_volt_data - Omap voltage specअगरic data.
 * @voltage_nominal:	The possible voltage value in uV
 * @sr_efuse_offs:	The offset of the efuse रेजिस्टर(from प्रणाली
 *			control module base address) from where to पढ़ो
 *			the n-target value क्रम the smartreflex module.
 * @sr_errminlimit:	Error min limit value क्रम smartreflex. This value
 *			dअगरfers at dअगरfernet opp and thus is linked
 *			with voltage.
 * @vp_errorgain:	Error gain value क्रम the voltage processor. This
 *			field also dअगरfers according to the voltage/opp.
 */
काष्ठा omap_volt_data अणु
	u32	volt_nominal;
	u32	sr_efuse_offs;
	u8	sr_errminlimit;
	u8	vp_errgain;
पूर्ण;
काष्ठा voltageकरोमुख्य;

काष्ठा voltageकरोमुख्य *voltdm_lookup(स्थिर अक्षर *name);
पूर्णांक voltdm_scale(काष्ठा voltageकरोमुख्य *voltdm, अचिन्हित दीर्घ target_volt);
अचिन्हित दीर्घ voltdm_get_voltage(काष्ठा voltageकरोमुख्य *voltdm);
काष्ठा omap_volt_data *omap_voltage_get_voltdata(काष्ठा voltageकरोमुख्य *voltdm,
		अचिन्हित दीर्घ volt);
#पूर्ण_अगर
