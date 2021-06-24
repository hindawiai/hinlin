<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright Intel Corp. 2018 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/nd.h>
#समावेश "pmem.h"
#समावेश "pfn.h"
#समावेश "nd.h"
#समावेश "nd-core.h"

sमाप_प्रकार security_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);

	/*
	 * For the test version we need to poll the "hardware" in order
	 * to get the updated status क्रम unlock testing.
	 */
	nvdimm->sec.flags = nvdimm_security_flags(nvdimm, NVDIMM_USER);

	अगर (test_bit(NVDIMM_SECURITY_DISABLED, &nvdimm->sec.flags))
		वापस प्र_लिखो(buf, "disabled\n");
	अगर (test_bit(NVDIMM_SECURITY_UNLOCKED, &nvdimm->sec.flags))
		वापस प्र_लिखो(buf, "unlocked\n");
	अगर (test_bit(NVDIMM_SECURITY_LOCKED, &nvdimm->sec.flags))
		वापस प्र_लिखो(buf, "locked\n");
	वापस -ENOTTY;
पूर्ण
