<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/device.h>
#समावेश <linux/cpu.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/nospec-branch.h>

sमाप_प्रकार cpu_show_spectre_v1(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "Mitigation: __user pointer sanitization\n");
पूर्ण

sमाप_प्रकार cpu_show_spectre_v2(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अगर (test_facility(156))
		वापस प्र_लिखो(buf, "Mitigation: etokens\n");
	अगर (__is_defined(CC_USING_EXPOLINE) && !nospec_disable)
		वापस प्र_लिखो(buf, "Mitigation: execute trampolines\n");
	अगर (__test_facility(82, S390_lowcore.alt_stfle_fac_list))
		वापस प्र_लिखो(buf, "Mitigation: limited branch prediction\n");
	वापस प्र_लिखो(buf, "Vulnerable\n");
पूर्ण
