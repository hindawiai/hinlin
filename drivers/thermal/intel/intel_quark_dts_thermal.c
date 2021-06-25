<शैली गुरु>
/*
 * पूर्णांकel_quark_dts_thermal.c
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2015 Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * Contact Inक्रमmation:
 *  Ong Boon Leong <boon.leong.ong@पूर्णांकel.com>
 *  Intel Malaysia, Penang
 *
 * BSD LICENSE
 *
 * Copyright(c) 2015 Intel Corporation.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the करोcumentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Quark DTS thermal driver is implemented by referencing
 * पूर्णांकel_soc_dts_thermal.c.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/thermal.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/iosf_mbi.h>

/* DTS reset is programmed via QRK_MBI_UNIT_SOC */
#घोषणा QRK_DTS_REG_OFFSET_RESET	0x34
#घोषणा QRK_DTS_RESET_BIT		BIT(0)

/* DTS enable is programmed via QRK_MBI_UNIT_RMU */
#घोषणा QRK_DTS_REG_OFFSET_ENABLE	0xB0
#घोषणा QRK_DTS_ENABLE_BIT		BIT(15)

/* Temperature Register is पढ़ो via QRK_MBI_UNIT_RMU */
#घोषणा QRK_DTS_REG_OFFSET_TEMP		0xB1
#घोषणा QRK_DTS_MASK_TEMP		0xFF
#घोषणा QRK_DTS_OFFSET_TEMP		0
#घोषणा QRK_DTS_OFFSET_REL_TEMP		16
#घोषणा QRK_DTS_TEMP_BASE		50

/* Programmable Trip Poपूर्णांक Register is configured via QRK_MBI_UNIT_RMU */
#घोषणा QRK_DTS_REG_OFFSET_PTPS		0xB2
#घोषणा QRK_DTS_MASK_TP_THRES		0xFF
#घोषणा QRK_DTS_SHIFT_TP		8
#घोषणा QRK_DTS_ID_TP_CRITICAL		0
#घोषणा QRK_DTS_SAFE_TP_THRES		105

/* Thermal Sensor Register Lock */
#घोषणा QRK_DTS_REG_OFFSET_LOCK		0x71
#घोषणा QRK_DTS_LOCK_BIT		BIT(5)

/* Quark DTS has 2 trip poपूर्णांकs: hot & catastrophic */
#घोषणा QRK_MAX_DTS_TRIPS	2
/* If DTS not locked, all trip poपूर्णांकs are configurable */
#घोषणा QRK_DTS_WR_MASK_SET	0x3
/* If DTS locked, all trip poपूर्णांकs are not configurable */
#घोषणा QRK_DTS_WR_MASK_CLR	0

#घोषणा DEFAULT_POLL_DELAY	2000

काष्ठा soc_sensor_entry अणु
	bool locked;
	u32 store_ptps;
	u32 store_dts_enable;
	काष्ठा thermal_zone_device *tzone;
पूर्ण;

अटल काष्ठा soc_sensor_entry *soc_dts;

अटल पूर्णांक polling_delay = DEFAULT_POLL_DELAY;
module_param(polling_delay, पूर्णांक, 0644);
MODULE_PARM_DESC(polling_delay,
	"Polling interval for checking trip points (in milliseconds)");

अटल DEFINE_MUTEX(dts_update_mutex);

अटल पूर्णांक soc_dts_enable(काष्ठा thermal_zone_device *tzd)
अणु
	u32 out;
	काष्ठा soc_sensor_entry *aux_entry = tzd->devdata;
	पूर्णांक ret;

	ret = iosf_mbi_पढ़ो(QRK_MBI_UNIT_RMU, MBI_REG_READ,
			    QRK_DTS_REG_OFFSET_ENABLE, &out);
	अगर (ret)
		वापस ret;

	अगर (out & QRK_DTS_ENABLE_BIT)
		वापस 0;

	अगर (!aux_entry->locked) अणु
		out |= QRK_DTS_ENABLE_BIT;
		ret = iosf_mbi_ग_लिखो(QRK_MBI_UNIT_RMU, MBI_REG_WRITE,
				     QRK_DTS_REG_OFFSET_ENABLE, out);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		pr_info("DTS is locked. Cannot enable DTS\n");
		ret = -EPERM;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक soc_dts_disable(काष्ठा thermal_zone_device *tzd)
अणु
	u32 out;
	काष्ठा soc_sensor_entry *aux_entry = tzd->devdata;
	पूर्णांक ret;

	ret = iosf_mbi_पढ़ो(QRK_MBI_UNIT_RMU, MBI_REG_READ,
			    QRK_DTS_REG_OFFSET_ENABLE, &out);
	अगर (ret)
		वापस ret;

	अगर (!(out & QRK_DTS_ENABLE_BIT))
		वापस 0;

	अगर (!aux_entry->locked) अणु
		out &= ~QRK_DTS_ENABLE_BIT;
		ret = iosf_mbi_ग_लिखो(QRK_MBI_UNIT_RMU, MBI_REG_WRITE,
				     QRK_DTS_REG_OFFSET_ENABLE, out);

		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		pr_info("DTS is locked. Cannot disable DTS\n");
		ret = -EPERM;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक _get_trip_temp(पूर्णांक trip, पूर्णांक *temp)
अणु
	पूर्णांक status;
	u32 out;

	mutex_lock(&dts_update_mutex);
	status = iosf_mbi_पढ़ो(QRK_MBI_UNIT_RMU, MBI_REG_READ,
			       QRK_DTS_REG_OFFSET_PTPS, &out);
	mutex_unlock(&dts_update_mutex);

	अगर (status)
		वापस status;

	/*
	 * Thermal Sensor Programmable Trip Poपूर्णांक Register has 8-bit
	 * fields क्रम critical (catastrophic) and hot set trip poपूर्णांक
	 * thresholds. The threshold value is always offset by its
	 * temperature base (50 degree Celsius).
	 */
	*temp = (out >> (trip * QRK_DTS_SHIFT_TP)) & QRK_DTS_MASK_TP_THRES;
	*temp -= QRK_DTS_TEMP_BASE;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sys_get_trip_temp(काष्ठा thermal_zone_device *tzd,
				पूर्णांक trip, पूर्णांक *temp)
अणु
	वापस _get_trip_temp(trip, temp);
पूर्ण

अटल अंतरभूत पूर्णांक sys_get_crit_temp(काष्ठा thermal_zone_device *tzd, पूर्णांक *temp)
अणु
	वापस _get_trip_temp(QRK_DTS_ID_TP_CRITICAL, temp);
पूर्ण

अटल पूर्णांक update_trip_temp(काष्ठा soc_sensor_entry *aux_entry,
				पूर्णांक trip, पूर्णांक temp)
अणु
	u32 out;
	u32 temp_out;
	u32 store_ptps;
	पूर्णांक ret;

	mutex_lock(&dts_update_mutex);
	अगर (aux_entry->locked) अणु
		ret = -EPERM;
		जाओ failed;
	पूर्ण

	ret = iosf_mbi_पढ़ो(QRK_MBI_UNIT_RMU, MBI_REG_READ,
			    QRK_DTS_REG_OFFSET_PTPS, &store_ptps);
	अगर (ret)
		जाओ failed;

	/*
	 * Protection against unsafe trip poपूर्णांक thresdhold value.
	 * As Quark X1000 data-sheet करोes not provide any recommendation
	 * regarding the safe trip poपूर्णांक threshold value to use, we choose
	 * the safe value according to the threshold value set by UEFI BIOS.
	 */
	अगर (temp > QRK_DTS_SAFE_TP_THRES)
		temp = QRK_DTS_SAFE_TP_THRES;

	/*
	 * Thermal Sensor Programmable Trip Poपूर्णांक Register has 8-bit
	 * fields क्रम critical (catastrophic) and hot set trip poपूर्णांक
	 * thresholds. The threshold value is always offset by its
	 * temperature base (50 degree Celsius).
	 */
	temp_out = temp + QRK_DTS_TEMP_BASE;
	out = (store_ptps & ~(QRK_DTS_MASK_TP_THRES <<
		(trip * QRK_DTS_SHIFT_TP)));
	out |= (temp_out & QRK_DTS_MASK_TP_THRES) <<
		(trip * QRK_DTS_SHIFT_TP);

	ret = iosf_mbi_ग_लिखो(QRK_MBI_UNIT_RMU, MBI_REG_WRITE,
			     QRK_DTS_REG_OFFSET_PTPS, out);

failed:
	mutex_unlock(&dts_update_mutex);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक sys_set_trip_temp(काष्ठा thermal_zone_device *tzd, पूर्णांक trip,
				पूर्णांक temp)
अणु
	वापस update_trip_temp(tzd->devdata, trip, temp);
पूर्ण

अटल पूर्णांक sys_get_trip_type(काष्ठा thermal_zone_device *thermal,
		पूर्णांक trip, क्रमागत thermal_trip_type *type)
अणु
	अगर (trip)
		*type = THERMAL_TRIP_HOT;
	अन्यथा
		*type = THERMAL_TRIP_CRITICAL;

	वापस 0;
पूर्ण

अटल पूर्णांक sys_get_curr_temp(काष्ठा thermal_zone_device *tzd,
				पूर्णांक *temp)
अणु
	u32 out;
	पूर्णांक ret;

	mutex_lock(&dts_update_mutex);
	ret = iosf_mbi_पढ़ो(QRK_MBI_UNIT_RMU, MBI_REG_READ,
			    QRK_DTS_REG_OFFSET_TEMP, &out);
	mutex_unlock(&dts_update_mutex);

	अगर (ret)
		वापस ret;

	/*
	 * Thermal Sensor Temperature Register has 8-bit field
	 * क्रम temperature value (offset by temperature base
	 * 50 degree Celsius).
	 */
	out = (out >> QRK_DTS_OFFSET_TEMP) & QRK_DTS_MASK_TEMP;
	*temp = out - QRK_DTS_TEMP_BASE;

	वापस 0;
पूर्ण

अटल पूर्णांक sys_change_mode(काष्ठा thermal_zone_device *tzd,
			   क्रमागत thermal_device_mode mode)
अणु
	पूर्णांक ret;

	mutex_lock(&dts_update_mutex);
	अगर (mode == THERMAL_DEVICE_ENABLED)
		ret = soc_dts_enable(tzd);
	अन्यथा
		ret = soc_dts_disable(tzd);
	mutex_unlock(&dts_update_mutex);

	वापस ret;
पूर्ण

अटल काष्ठा thermal_zone_device_ops tzone_ops = अणु
	.get_temp = sys_get_curr_temp,
	.get_trip_temp = sys_get_trip_temp,
	.get_trip_type = sys_get_trip_type,
	.set_trip_temp = sys_set_trip_temp,
	.get_crit_temp = sys_get_crit_temp,
	.change_mode = sys_change_mode,
पूर्ण;

अटल व्योम मुक्त_soc_dts(काष्ठा soc_sensor_entry *aux_entry)
अणु
	अगर (aux_entry) अणु
		अगर (!aux_entry->locked) अणु
			mutex_lock(&dts_update_mutex);
			iosf_mbi_ग_लिखो(QRK_MBI_UNIT_RMU, MBI_REG_WRITE,
				       QRK_DTS_REG_OFFSET_ENABLE,
				       aux_entry->store_dts_enable);

			iosf_mbi_ग_लिखो(QRK_MBI_UNIT_RMU, MBI_REG_WRITE,
				       QRK_DTS_REG_OFFSET_PTPS,
				       aux_entry->store_ptps);
			mutex_unlock(&dts_update_mutex);
		पूर्ण
		thermal_zone_device_unरेजिस्टर(aux_entry->tzone);
		kमुक्त(aux_entry);
	पूर्ण
पूर्ण

अटल काष्ठा soc_sensor_entry *alloc_soc_dts(व्योम)
अणु
	काष्ठा soc_sensor_entry *aux_entry;
	पूर्णांक err;
	u32 out;
	पूर्णांक wr_mask;

	aux_entry = kzalloc(माप(*aux_entry), GFP_KERNEL);
	अगर (!aux_entry) अणु
		err = -ENOMEM;
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* Check अगर DTS रेजिस्टर is locked */
	err = iosf_mbi_पढ़ो(QRK_MBI_UNIT_RMU, MBI_REG_READ,
			    QRK_DTS_REG_OFFSET_LOCK, &out);
	अगर (err)
		जाओ err_ret;

	अगर (out & QRK_DTS_LOCK_BIT) अणु
		aux_entry->locked = true;
		wr_mask = QRK_DTS_WR_MASK_CLR;
	पूर्ण अन्यथा अणु
		aux_entry->locked = false;
		wr_mask = QRK_DTS_WR_MASK_SET;
	पूर्ण

	/* Store DTS शेष state अगर DTS रेजिस्टरs are not locked */
	अगर (!aux_entry->locked) अणु
		/* Store DTS शेष enable क्रम restore on निकास */
		err = iosf_mbi_पढ़ो(QRK_MBI_UNIT_RMU, MBI_REG_READ,
				    QRK_DTS_REG_OFFSET_ENABLE,
				    &aux_entry->store_dts_enable);
		अगर (err)
			जाओ err_ret;

		/* Store DTS शेष PTPS रेजिस्टर क्रम restore on निकास */
		err = iosf_mbi_पढ़ो(QRK_MBI_UNIT_RMU, MBI_REG_READ,
				    QRK_DTS_REG_OFFSET_PTPS,
				    &aux_entry->store_ptps);
		अगर (err)
			जाओ err_ret;
	पूर्ण

	aux_entry->tzone = thermal_zone_device_रेजिस्टर("quark_dts",
			QRK_MAX_DTS_TRIPS,
			wr_mask,
			aux_entry, &tzone_ops, शून्य, 0, polling_delay);
	अगर (IS_ERR(aux_entry->tzone)) अणु
		err = PTR_ERR(aux_entry->tzone);
		जाओ err_ret;
	पूर्ण

	err = thermal_zone_device_enable(aux_entry->tzone);
	अगर (err)
		जाओ err_aux_status;

	वापस aux_entry;

err_aux_status:
	thermal_zone_device_unरेजिस्टर(aux_entry->tzone);
err_ret:
	kमुक्त(aux_entry);
	वापस ERR_PTR(err);
पूर्ण

अटल स्थिर काष्ठा x86_cpu_id qrk_thermal_ids[] __initस्थिर  = अणु
	X86_MATCH_VENDOR_FAM_MODEL(INTEL, 5, INTEL_FAM5_QUARK_X1000, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, qrk_thermal_ids);

अटल पूर्णांक __init पूर्णांकel_quark_thermal_init(व्योम)
अणु
	पूर्णांक err = 0;

	अगर (!x86_match_cpu(qrk_thermal_ids) || !iosf_mbi_available())
		वापस -ENODEV;

	soc_dts = alloc_soc_dts();
	अगर (IS_ERR(soc_dts)) अणु
		err = PTR_ERR(soc_dts);
		जाओ err_मुक्त;
	पूर्ण

	वापस 0;

err_मुक्त:
	मुक्त_soc_dts(soc_dts);
	वापस err;
पूर्ण

अटल व्योम __निकास पूर्णांकel_quark_thermal_निकास(व्योम)
अणु
	मुक्त_soc_dts(soc_dts);
पूर्ण

module_init(पूर्णांकel_quark_thermal_init)
module_निकास(पूर्णांकel_quark_thermal_निकास)

MODULE_DESCRIPTION("Intel Quark DTS Thermal Driver");
MODULE_AUTHOR("Ong Boon Leong <boon.leong.ong@intel.com>");
MODULE_LICENSE("Dual BSD/GPL");
