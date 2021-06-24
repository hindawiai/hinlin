<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "habanalabs.h"

#समावेश <linux/slab.h>

पूर्णांक hl_asid_init(काष्ठा hl_device *hdev)
अणु
	hdev->asid_biपंचांगap = kसुस्मृति(BITS_TO_LONGS(hdev->asic_prop.max_asid),
					माप(*hdev->asid_biपंचांगap), GFP_KERNEL);
	अगर (!hdev->asid_biपंचांगap)
		वापस -ENOMEM;

	mutex_init(&hdev->asid_mutex);

	/* ASID 0 is reserved क्रम the kernel driver and device CPU */
	set_bit(0, hdev->asid_biपंचांगap);

	वापस 0;
पूर्ण

व्योम hl_asid_fini(काष्ठा hl_device *hdev)
अणु
	mutex_destroy(&hdev->asid_mutex);
	kमुक्त(hdev->asid_biपंचांगap);
पूर्ण

अचिन्हित दीर्घ hl_asid_alloc(काष्ठा hl_device *hdev)
अणु
	अचिन्हित दीर्घ found;

	mutex_lock(&hdev->asid_mutex);

	found = find_first_zero_bit(hdev->asid_biपंचांगap,
					hdev->asic_prop.max_asid);
	अगर (found == hdev->asic_prop.max_asid)
		found = 0;
	अन्यथा
		set_bit(found, hdev->asid_biपंचांगap);

	mutex_unlock(&hdev->asid_mutex);

	वापस found;
पूर्ण

व्योम hl_asid_मुक्त(काष्ठा hl_device *hdev, अचिन्हित दीर्घ asid)
अणु
	अगर (asid == HL_KERNEL_ASID_ID || asid >= hdev->asic_prop.max_asid) अणु
		dev_crit(hdev->dev, "Invalid ASID %lu", asid);
		वापस;
	पूर्ण

	clear_bit(asid, hdev->asid_biपंचांगap);
पूर्ण
