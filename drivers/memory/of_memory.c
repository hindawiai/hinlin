<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenFirmware helpers क्रम memory drivers
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 * Copyright (C) 2019 Samsung Electronics Co., Ltd.
 * Copyright (C) 2020 Krzysztof Kozlowski <krzk@kernel.org>
 */

#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/gfp.h>
#समावेश <linux/export.h>

#समावेश "jedec_ddr.h"
#समावेश "of_memory.h"

/**
 * of_get_min_tck() - extract min timing values क्रम ddr
 * @np: poपूर्णांकer to ddr device tree node
 * @dev: device requesting क्रम min timing values
 *
 * Populates the lpddr2_min_tck काष्ठाure by extracting data
 * from device tree node. Returns a poपूर्णांकer to the populated
 * काष्ठाure. If any error in populating the काष्ठाure, वापसs
 * शेष min timings provided by JEDEC.
 */
स्थिर काष्ठा lpddr2_min_tck *of_get_min_tck(काष्ठा device_node *np,
					    काष्ठा device *dev)
अणु
	पूर्णांक			ret = 0;
	काष्ठा lpddr2_min_tck	*min;

	min = devm_kzalloc(dev, माप(*min), GFP_KERNEL);
	अगर (!min)
		जाओ शेष_min_tck;

	ret |= of_property_पढ़ो_u32(np, "tRPab-min-tck", &min->tRPab);
	ret |= of_property_पढ़ो_u32(np, "tRCD-min-tck", &min->tRCD);
	ret |= of_property_पढ़ो_u32(np, "tWR-min-tck", &min->tWR);
	ret |= of_property_पढ़ो_u32(np, "tRASmin-min-tck", &min->tRASmin);
	ret |= of_property_पढ़ो_u32(np, "tRRD-min-tck", &min->tRRD);
	ret |= of_property_पढ़ो_u32(np, "tWTR-min-tck", &min->tWTR);
	ret |= of_property_पढ़ो_u32(np, "tXP-min-tck", &min->tXP);
	ret |= of_property_पढ़ो_u32(np, "tRTP-min-tck", &min->tRTP);
	ret |= of_property_पढ़ो_u32(np, "tCKE-min-tck", &min->tCKE);
	ret |= of_property_पढ़ो_u32(np, "tCKESR-min-tck", &min->tCKESR);
	ret |= of_property_पढ़ो_u32(np, "tFAW-min-tck", &min->tFAW);

	अगर (ret) अणु
		devm_kमुक्त(dev, min);
		जाओ शेष_min_tck;
	पूर्ण

	वापस min;

शेष_min_tck:
	dev_warn(dev, "Using default min-tck values\n");
	वापस &lpddr2_jedec_min_tck;
पूर्ण
EXPORT_SYMBOL(of_get_min_tck);

अटल पूर्णांक of_करो_get_timings(काष्ठा device_node *np,
			     काष्ठा lpddr2_timings *tim)
अणु
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "max-freq", &tim->max_freq);
	ret |= of_property_पढ़ो_u32(np, "min-freq", &tim->min_freq);
	ret |= of_property_पढ़ो_u32(np, "tRPab", &tim->tRPab);
	ret |= of_property_पढ़ो_u32(np, "tRCD", &tim->tRCD);
	ret |= of_property_पढ़ो_u32(np, "tWR", &tim->tWR);
	ret |= of_property_पढ़ो_u32(np, "tRAS-min", &tim->tRAS_min);
	ret |= of_property_पढ़ो_u32(np, "tRRD", &tim->tRRD);
	ret |= of_property_पढ़ो_u32(np, "tWTR", &tim->tWTR);
	ret |= of_property_पढ़ो_u32(np, "tXP", &tim->tXP);
	ret |= of_property_पढ़ो_u32(np, "tRTP", &tim->tRTP);
	ret |= of_property_पढ़ो_u32(np, "tCKESR", &tim->tCKESR);
	ret |= of_property_पढ़ो_u32(np, "tDQSCK-max", &tim->tDQSCK_max);
	ret |= of_property_पढ़ो_u32(np, "tFAW", &tim->tFAW);
	ret |= of_property_पढ़ो_u32(np, "tZQCS", &tim->tZQCS);
	ret |= of_property_पढ़ो_u32(np, "tZQCL", &tim->tZQCL);
	ret |= of_property_पढ़ो_u32(np, "tZQinit", &tim->tZQinit);
	ret |= of_property_पढ़ो_u32(np, "tRAS-max-ns", &tim->tRAS_max_ns);
	ret |= of_property_पढ़ो_u32(np, "tDQSCK-max-derated",
				    &tim->tDQSCK_max_derated);

	वापस ret;
पूर्ण

/**
 * of_get_ddr_timings() - extracts the ddr timings and updates no of
 * frequencies available.
 * @np_ddr: Poपूर्णांकer to ddr device tree node
 * @dev: Device requesting क्रम ddr timings
 * @device_type: Type of ddr(LPDDR2 S2/S4)
 * @nr_frequencies: No of frequencies available क्रम ddr
 * (updated by this function)
 *
 * Populates lpddr2_timings काष्ठाure by extracting data from device
 * tree node. Returns poपूर्णांकer to populated काष्ठाure. If any error
 * जबतक populating, वापसs शेष timings provided by JEDEC.
 */
स्थिर काष्ठा lpddr2_timings *of_get_ddr_timings(काष्ठा device_node *np_ddr,
						काष्ठा device *dev,
						u32 device_type,
						u32 *nr_frequencies)
अणु
	काष्ठा lpddr2_timings	*timings = शून्य;
	u32			arr_sz = 0, i = 0;
	काष्ठा device_node	*np_tim;
	अक्षर			*tim_compat = शून्य;

	चयन (device_type) अणु
	हाल DDR_TYPE_LPDDR2_S2:
	हाल DDR_TYPE_LPDDR2_S4:
		tim_compat = "jedec,lpddr2-timings";
		अवरोध;
	शेष:
		dev_warn(dev, "Unsupported memory type\n");
	पूर्ण

	क्रम_each_child_of_node(np_ddr, np_tim)
		अगर (of_device_is_compatible(np_tim, tim_compat))
			arr_sz++;

	अगर (arr_sz)
		timings = devm_kसुस्मृति(dev, arr_sz, माप(*timings),
				       GFP_KERNEL);

	अगर (!timings)
		जाओ शेष_timings;

	क्रम_each_child_of_node(np_ddr, np_tim) अणु
		अगर (of_device_is_compatible(np_tim, tim_compat)) अणु
			अगर (of_करो_get_timings(np_tim, &timings[i])) अणु
				devm_kमुक्त(dev, timings);
				जाओ शेष_timings;
			पूर्ण
			i++;
		पूर्ण
	पूर्ण

	*nr_frequencies = arr_sz;

	वापस timings;

शेष_timings:
	dev_warn(dev, "Using default memory timings\n");
	*nr_frequencies = ARRAY_SIZE(lpddr2_jedec_timings);
	वापस lpddr2_jedec_timings;
पूर्ण
EXPORT_SYMBOL(of_get_ddr_timings);

/**
 * of_lpddr3_get_min_tck() - extract min timing values क्रम lpddr3
 * @np: poपूर्णांकer to ddr device tree node
 * @dev: device requesting क्रम min timing values
 *
 * Populates the lpddr3_min_tck काष्ठाure by extracting data
 * from device tree node. Returns a poपूर्णांकer to the populated
 * काष्ठाure. If any error in populating the काष्ठाure, वापसs शून्य.
 */
स्थिर काष्ठा lpddr3_min_tck *of_lpddr3_get_min_tck(काष्ठा device_node *np,
						   काष्ठा device *dev)
अणु
	पूर्णांक			ret = 0;
	काष्ठा lpddr3_min_tck	*min;

	min = devm_kzalloc(dev, माप(*min), GFP_KERNEL);
	अगर (!min)
		जाओ शेष_min_tck;

	ret |= of_property_पढ़ो_u32(np, "tRFC-min-tck", &min->tRFC);
	ret |= of_property_पढ़ो_u32(np, "tRRD-min-tck", &min->tRRD);
	ret |= of_property_पढ़ो_u32(np, "tRPab-min-tck", &min->tRPab);
	ret |= of_property_पढ़ो_u32(np, "tRPpb-min-tck", &min->tRPpb);
	ret |= of_property_पढ़ो_u32(np, "tRCD-min-tck", &min->tRCD);
	ret |= of_property_पढ़ो_u32(np, "tRC-min-tck", &min->tRC);
	ret |= of_property_पढ़ो_u32(np, "tRAS-min-tck", &min->tRAS);
	ret |= of_property_पढ़ो_u32(np, "tWTR-min-tck", &min->tWTR);
	ret |= of_property_पढ़ो_u32(np, "tWR-min-tck", &min->tWR);
	ret |= of_property_पढ़ो_u32(np, "tRTP-min-tck", &min->tRTP);
	ret |= of_property_पढ़ो_u32(np, "tW2W-C2C-min-tck", &min->tW2W_C2C);
	ret |= of_property_पढ़ो_u32(np, "tR2R-C2C-min-tck", &min->tR2R_C2C);
	ret |= of_property_पढ़ो_u32(np, "tWL-min-tck", &min->tWL);
	ret |= of_property_पढ़ो_u32(np, "tDQSCK-min-tck", &min->tDQSCK);
	ret |= of_property_पढ़ो_u32(np, "tRL-min-tck", &min->tRL);
	ret |= of_property_पढ़ो_u32(np, "tFAW-min-tck", &min->tFAW);
	ret |= of_property_पढ़ो_u32(np, "tXSR-min-tck", &min->tXSR);
	ret |= of_property_पढ़ो_u32(np, "tXP-min-tck", &min->tXP);
	ret |= of_property_पढ़ो_u32(np, "tCKE-min-tck", &min->tCKE);
	ret |= of_property_पढ़ो_u32(np, "tCKESR-min-tck", &min->tCKESR);
	ret |= of_property_पढ़ो_u32(np, "tMRD-min-tck", &min->tMRD);

	अगर (ret) अणु
		dev_warn(dev, "Errors while parsing min-tck values\n");
		devm_kमुक्त(dev, min);
		जाओ शेष_min_tck;
	पूर्ण

	वापस min;

शेष_min_tck:
	dev_warn(dev, "Using default min-tck values\n");
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(of_lpddr3_get_min_tck);

अटल पूर्णांक of_lpddr3_करो_get_timings(काष्ठा device_node *np,
				    काष्ठा lpddr3_timings *tim)
अणु
	पूर्णांक ret;

	/* The 'reg' param required since DT has changed, used as 'max-freq' */
	ret = of_property_पढ़ो_u32(np, "reg", &tim->max_freq);
	ret |= of_property_पढ़ो_u32(np, "min-freq", &tim->min_freq);
	ret |= of_property_पढ़ो_u32(np, "tRFC", &tim->tRFC);
	ret |= of_property_पढ़ो_u32(np, "tRRD", &tim->tRRD);
	ret |= of_property_पढ़ो_u32(np, "tRPab", &tim->tRPab);
	ret |= of_property_पढ़ो_u32(np, "tRPpb", &tim->tRPpb);
	ret |= of_property_पढ़ो_u32(np, "tRCD", &tim->tRCD);
	ret |= of_property_पढ़ो_u32(np, "tRC", &tim->tRC);
	ret |= of_property_पढ़ो_u32(np, "tRAS", &tim->tRAS);
	ret |= of_property_पढ़ो_u32(np, "tWTR", &tim->tWTR);
	ret |= of_property_पढ़ो_u32(np, "tWR", &tim->tWR);
	ret |= of_property_पढ़ो_u32(np, "tRTP", &tim->tRTP);
	ret |= of_property_पढ़ो_u32(np, "tW2W-C2C", &tim->tW2W_C2C);
	ret |= of_property_पढ़ो_u32(np, "tR2R-C2C", &tim->tR2R_C2C);
	ret |= of_property_पढ़ो_u32(np, "tFAW", &tim->tFAW);
	ret |= of_property_पढ़ो_u32(np, "tXSR", &tim->tXSR);
	ret |= of_property_पढ़ो_u32(np, "tXP", &tim->tXP);
	ret |= of_property_पढ़ो_u32(np, "tCKE", &tim->tCKE);
	ret |= of_property_पढ़ो_u32(np, "tCKESR", &tim->tCKESR);
	ret |= of_property_पढ़ो_u32(np, "tMRD", &tim->tMRD);

	वापस ret;
पूर्ण

/**
 * of_lpddr3_get_ddr_timings() - extracts the lpddr3 timings and updates no of
 * frequencies available.
 * @np_ddr: Poपूर्णांकer to ddr device tree node
 * @dev: Device requesting क्रम ddr timings
 * @device_type: Type of ddr
 * @nr_frequencies: No of frequencies available क्रम ddr
 * (updated by this function)
 *
 * Populates lpddr3_timings काष्ठाure by extracting data from device
 * tree node. Returns poपूर्णांकer to populated काष्ठाure. If any error
 * जबतक populating, वापसs शून्य.
 */
स्थिर काष्ठा lpddr3_timings
*of_lpddr3_get_ddr_timings(काष्ठा device_node *np_ddr, काष्ठा device *dev,
			   u32 device_type, u32 *nr_frequencies)
अणु
	काष्ठा lpddr3_timings	*timings = शून्य;
	u32			arr_sz = 0, i = 0;
	काष्ठा device_node	*np_tim;
	अक्षर			*tim_compat = शून्य;

	चयन (device_type) अणु
	हाल DDR_TYPE_LPDDR3:
		tim_compat = "jedec,lpddr3-timings";
		अवरोध;
	शेष:
		dev_warn(dev, "Unsupported memory type\n");
	पूर्ण

	क्रम_each_child_of_node(np_ddr, np_tim)
		अगर (of_device_is_compatible(np_tim, tim_compat))
			arr_sz++;

	अगर (arr_sz)
		timings = devm_kसुस्मृति(dev, arr_sz, माप(*timings),
				       GFP_KERNEL);

	अगर (!timings)
		जाओ शेष_timings;

	क्रम_each_child_of_node(np_ddr, np_tim) अणु
		अगर (of_device_is_compatible(np_tim, tim_compat)) अणु
			अगर (of_lpddr3_करो_get_timings(np_tim, &timings[i])) अणु
				devm_kमुक्त(dev, timings);
				जाओ शेष_timings;
			पूर्ण
			i++;
		पूर्ण
	पूर्ण

	*nr_frequencies = arr_sz;

	वापस timings;

शेष_timings:
	dev_warn(dev, "Failed to get timings\n");
	*nr_frequencies = 0;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(of_lpddr3_get_ddr_timings);
