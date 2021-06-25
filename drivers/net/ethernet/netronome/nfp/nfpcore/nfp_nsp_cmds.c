<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017 Netronome Systems, Inc. */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "nfp.h"
#समावेश "nfp_nsp.h"

काष्ठा nsp_identअगरy अणु
	u8 version[40];
	u8 flags;
	u8 br_primary;
	u8 br_secondary;
	u8 br_nsp;
	__le16 primary;
	__le16 secondary;
	__le16 nsp;
	u8 reserved[6];
	__le64 sensor_mask;
पूर्ण;

काष्ठा nfp_nsp_identअगरy *__nfp_nsp_identअगरy(काष्ठा nfp_nsp *nsp)
अणु
	काष्ठा nfp_nsp_identअगरy *nspi = शून्य;
	काष्ठा nsp_identअगरy *ni;
	पूर्णांक ret;

	अगर (nfp_nsp_get_abi_ver_minor(nsp) < 15)
		वापस शून्य;

	ni = kzalloc(माप(*ni), GFP_KERNEL);
	अगर (!ni)
		वापस शून्य;

	ret = nfp_nsp_पढ़ो_identअगरy(nsp, ni, माप(*ni));
	अगर (ret < 0) अणु
		nfp_err(nfp_nsp_cpp(nsp), "reading bsp version failed %d\n",
			ret);
		जाओ निकास_मुक्त;
	पूर्ण

	nspi = kzalloc(माप(*nspi), GFP_KERNEL);
	अगर (!nspi)
		जाओ निकास_मुक्त;

	स_नकल(nspi->version, ni->version, माप(nspi->version));
	nspi->version[माप(nspi->version) - 1] = '\0';
	nspi->flags = ni->flags;
	nspi->br_primary = ni->br_primary;
	nspi->br_secondary = ni->br_secondary;
	nspi->br_nsp = ni->br_nsp;
	nspi->primary = le16_to_cpu(ni->primary);
	nspi->secondary = le16_to_cpu(ni->secondary);
	nspi->nsp = le16_to_cpu(ni->nsp);
	nspi->sensor_mask = le64_to_cpu(ni->sensor_mask);

निकास_मुक्त:
	kमुक्त(ni);
	वापस nspi;
पूर्ण

काष्ठा nfp_sensors अणु
	__le32 chip_temp;
	__le32 assembly_घातer;
	__le32 assembly_12v_घातer;
	__le32 assembly_3v3_घातer;
पूर्ण;

पूर्णांक nfp_hwmon_पढ़ो_sensor(काष्ठा nfp_cpp *cpp, क्रमागत nfp_nsp_sensor_id id,
			  दीर्घ *val)
अणु
	काष्ठा nfp_sensors s;
	काष्ठा nfp_nsp *nsp;
	पूर्णांक ret;

	nsp = nfp_nsp_खोलो(cpp);
	अगर (IS_ERR(nsp))
		वापस PTR_ERR(nsp);

	ret = nfp_nsp_पढ़ो_sensors(nsp, BIT(id), &s, माप(s));
	nfp_nsp_बंद(nsp);

	अगर (ret < 0)
		वापस ret;

	चयन (id) अणु
	हाल NFP_SENSOR_CHIP_TEMPERATURE:
		*val = le32_to_cpu(s.chip_temp);
		अवरोध;
	हाल NFP_SENSOR_ASSEMBLY_POWER:
		*val = le32_to_cpu(s.assembly_घातer);
		अवरोध;
	हाल NFP_SENSOR_ASSEMBLY_12V_POWER:
		*val = le32_to_cpu(s.assembly_12v_घातer);
		अवरोध;
	हाल NFP_SENSOR_ASSEMBLY_3V3_POWER:
		*val = le32_to_cpu(s.assembly_3v3_घातer);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
