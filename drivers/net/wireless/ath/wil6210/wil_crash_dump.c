<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2015,2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#समावेश "wil6210.h"
#समावेश <linux/devcoredump.h>

अटल पूर्णांक wil_fw_get_crash_dump_bounds(काष्ठा wil6210_priv *wil,
					u32 *out_dump_size, u32 *out_host_min)
अणु
	पूर्णांक i;
	स्थिर काष्ठा fw_map *map;
	u32 host_min, host_max, पंचांगp_max;

	अगर (!out_dump_size)
		वापस -EINVAL;

	/* calculate the total size of the unpacked crash dump */
	BUILD_BUG_ON(ARRAY_SIZE(fw_mapping) == 0);
	map = &fw_mapping[0];
	host_min = map->host;
	host_max = map->host + (map->to - map->from);

	क्रम (i = 1; i < ARRAY_SIZE(fw_mapping); i++) अणु
		map = &fw_mapping[i];

		अगर (!map->crash_dump)
			जारी;

		अगर (map->host < host_min)
			host_min = map->host;

		पंचांगp_max = map->host + (map->to - map->from);
		अगर (पंचांगp_max > host_max)
			host_max = पंचांगp_max;
	पूर्ण

	*out_dump_size = host_max - host_min;
	अगर (out_host_min)
		*out_host_min = host_min;

	वापस 0;
पूर्ण

पूर्णांक wil_fw_copy_crash_dump(काष्ठा wil6210_priv *wil, व्योम *dest, u32 size)
अणु
	पूर्णांक i;
	स्थिर काष्ठा fw_map *map;
	व्योम *data;
	u32 host_min, dump_size, offset, len;

	अगर (wil_fw_get_crash_dump_bounds(wil, &dump_size, &host_min)) अणु
		wil_err(wil, "fail to obtain crash dump size\n");
		वापस -EINVAL;
	पूर्ण

	अगर (dump_size > size) अणु
		wil_err(wil, "not enough space for dump. Need %d have %d\n",
			dump_size, size);
		वापस -EINVAL;
	पूर्ण

	करोwn_ग_लिखो(&wil->mem_lock);

	अगर (test_bit(wil_status_suspending, wil->status) ||
	    test_bit(wil_status_suspended, wil->status)) अणु
		wil_err(wil,
			"suspend/resume in progress. cannot copy crash dump\n");
		up_ग_लिखो(&wil->mem_lock);
		वापस -EBUSY;
	पूर्ण

	/* copy to crash dump area */
	क्रम (i = 0; i < ARRAY_SIZE(fw_mapping); i++) अणु
		map = &fw_mapping[i];

		अगर (!map->crash_dump)
			जारी;

		data = (व्योम * __क्रमce)wil->csr + HOSTADDR(map->host);
		len = map->to - map->from;
		offset = map->host - host_min;

		wil_dbg_misc(wil,
			     "fw_copy_crash_dump: - dump %s, size %d, offset %d\n",
			     fw_mapping[i].name, len, offset);

		wil_स_नकल_fromio_32((व्योम * __क्रमce)(dest + offset),
				     (स्थिर व्योम __iomem * __क्रमce)data, len);
	पूर्ण

	up_ग_लिखो(&wil->mem_lock);

	वापस 0;
पूर्ण

व्योम wil_fw_core_dump(काष्ठा wil6210_priv *wil)
अणु
	व्योम *fw_dump_data;
	u32 fw_dump_size;

	अगर (wil_fw_get_crash_dump_bounds(wil, &fw_dump_size, शून्य)) अणु
		wil_err(wil, "fail to get fw dump size\n");
		वापस;
	पूर्ण

	fw_dump_data = vzalloc(fw_dump_size);
	अगर (!fw_dump_data)
		वापस;

	अगर (wil_fw_copy_crash_dump(wil, fw_dump_data, fw_dump_size)) अणु
		vमुक्त(fw_dump_data);
		वापस;
	पूर्ण
	/* fw_dump_data will be मुक्त in device coredump release function
	 * after 5 min
	 */
	dev_coredumpv(wil_to_dev(wil), fw_dump_data, fw_dump_size, GFP_KERNEL);
	wil_info(wil, "fw core dumped, size %d bytes\n", fw_dump_size);
पूर्ण
