<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Implementation of get_cpuid().
 *
 * Copyright IBM Corp. 2014, 2018
 * Author(s): Alexander Yarygin <yarygin@linux.vnet.ibm.com>
 *	      Thomas Richter <पंचांगricht@linux.vnet.ibm.com>
 */

#समावेश <sys/types.h>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>

#समावेश "../../util/header.h"

#घोषणा SYSINFO_MANU	"Manufacturer:"
#घोषणा SYSINFO_TYPE	"Type:"
#घोषणा SYSINFO_MODEL	"Model:"
#घोषणा SRVLVL_CPUMF	"CPU-MF:"
#घोषणा SRVLVL_VERSION	"version="
#घोषणा SRVLVL_AUTHORIZATION	"authorization="
#घोषणा SYSINFO		"/proc/sysinfo"
#घोषणा SRVLVL		"/proc/service_levels"

पूर्णांक get_cpuid(अक्षर *buffer, माप_प्रकार sz)
अणु
	अक्षर *cp, *line = शून्य, *line2;
	अक्षर type[8], model[33], version[8], manufacturer[32], authorization[8];
	पूर्णांक tpsize = 0, mdsize = 0, vssize = 0, mfsize = 0, atsize = 0;
	पूर्णांक पढ़ो;
	अचिन्हित दीर्घ line_sz;
	माप_प्रकार nbytes;
	खाता *sysinfo;

	/*
	 * Scan /proc/sysinfo line by line and पढ़ो out values क्रम
	 * Manufacturer:, Type: and Model:, क्रम example:
	 * Manufacturer:    IBM
	 * Type:            2964
	 * Model:           702              N96
	 * The first word is the Model Capacity and the second word is
	 * Model (can be omitted). Both words have a maximum size of 16
	 * bytes.
	 */
	स_रखो(manufacturer, 0, माप(manufacturer));
	स_रखो(type, 0, माप(type));
	स_रखो(model, 0, माप(model));
	स_रखो(version, 0, माप(version));
	स_रखो(authorization, 0, माप(authorization));

	sysinfo = ख_खोलो(SYSINFO, "r");
	अगर (sysinfo == शून्य)
		वापस त्रुटि_सं;

	जबतक ((पढ़ो = getline(&line, &line_sz, sysinfo)) != -1) अणु
		अगर (!म_भेदन(line, SYSINFO_MANU, म_माप(SYSINFO_MANU))) अणु
			line2 = line + म_माप(SYSINFO_MANU);

			जबतक ((cp = म_मोहर_r(line2, "\n ", &line2))) अणु
				mfsize += scnम_लिखो(manufacturer + mfsize,
						    माप(manufacturer) - mfsize, "%s", cp);
			पूर्ण
		पूर्ण

		अगर (!म_भेदन(line, SYSINFO_TYPE, म_माप(SYSINFO_TYPE))) अणु
			line2 = line + म_माप(SYSINFO_TYPE);

			जबतक ((cp = म_मोहर_r(line2, "\n ", &line2))) अणु
				tpsize += scnम_लिखो(type + tpsize,
						    माप(type) - tpsize, "%s", cp);
			पूर्ण
		पूर्ण

		अगर (!म_भेदन(line, SYSINFO_MODEL, म_माप(SYSINFO_MODEL))) अणु
			line2 = line + म_माप(SYSINFO_MODEL);

			जबतक ((cp = म_मोहर_r(line2, "\n ", &line2))) अणु
				mdsize += scnम_लिखो(model + mdsize, माप(model) - mdsize,
						    "%s%s", model[0] ? "," : "", cp);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	ख_बंद(sysinfo);

	/* Missing manufacturer, type or model inक्रमmation should not happen */
	अगर (!manufacturer[0] || !type[0] || !model[0])
		वापस EINVAL;

	/*
	 * Scan /proc/service_levels and वापस the CPU-MF counter facility
	 * version number and authorization level.
	 * Optional, करोes not exist on z/VM guests.
	 */
	sysinfo = ख_खोलो(SRVLVL, "r");
	अगर (sysinfo == शून्य)
		जाओ skip_sysinfo;
	जबतक ((पढ़ो = getline(&line, &line_sz, sysinfo)) != -1) अणु
		अगर (म_भेदन(line, SRVLVL_CPUMF, म_माप(SRVLVL_CPUMF)))
			जारी;

		line2 = line + म_माप(SRVLVL_CPUMF);
		जबतक ((cp = म_मोहर_r(line2, "\n ", &line2))) अणु
			अगर (!म_भेदन(cp, SRVLVL_VERSION,
				     म_माप(SRVLVL_VERSION))) अणु
				अक्षर *sep = म_अक्षर(cp, '=');

				vssize += scnम_लिखो(version + vssize,
						    माप(version) - vssize, "%s", sep + 1);
			पूर्ण
			अगर (!म_भेदन(cp, SRVLVL_AUTHORIZATION,
				     म_माप(SRVLVL_AUTHORIZATION))) अणु
				अक्षर *sep = म_अक्षर(cp, '=');

				atsize += scnम_लिखो(authorization + atsize,
						    माप(authorization) - atsize, "%s", sep + 1);
			पूर्ण
		पूर्ण
	पूर्ण
	ख_बंद(sysinfo);

skip_sysinfo:
	मुक्त(line);

	अगर (version[0] && authorization[0] )
		nbytes = snम_लिखो(buffer, sz, "%s,%s,%s,%s,%s",
				  manufacturer, type, model, version,
				  authorization);
	अन्यथा
		nbytes = snम_लिखो(buffer, sz, "%s,%s,%s", manufacturer, type,
				  model);
	वापस (nbytes >= sz) ? ENOBUFS : 0;
पूर्ण

अक्षर *get_cpuid_str(काष्ठा perf_pmu *pmu __maybe_unused)
अणु
	अक्षर *buf = दो_स्मृति(128);

	अगर (buf && get_cpuid(buf, 128))
		zमुक्त(&buf);
	वापस buf;
पूर्ण
