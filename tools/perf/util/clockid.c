<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <subcmd/parse-options.h>
#समावेश <मानकपन.स>
#समावेश <समय.स>
#समावेश <strings.h>
#समावेश <linux/समय64.h>
#समावेश "debug.h"
#समावेश "clockid.h"
#समावेश "record.h"

काष्ठा घड़ीid_map अणु
	स्थिर अक्षर *name;
	पूर्णांक घड़ीid;
पूर्ण;

#घोषणा CLOCKID_MAP(n, c)	\
	अणु .name = n, .घड़ीid = (c), पूर्ण

#घोषणा CLOCKID_END	अणु .name = शून्य, पूर्ण


/*
 * Add the missing ones, we need to build on many distros...
 */
#अगर_अघोषित CLOCK_MONOTONIC_RAW
#घोषणा CLOCK_MONOTONIC_RAW 4
#पूर्ण_अगर
#अगर_अघोषित CLOCK_BOOTTIME
#घोषणा CLOCK_BOOTTIME 7
#पूर्ण_अगर
#अगर_अघोषित CLOCK_TAI
#घोषणा CLOCK_TAI 11
#पूर्ण_अगर

अटल स्थिर काष्ठा घड़ीid_map घड़ीids[] = अणु
	/* available क्रम all events, NMI safe */
	CLOCKID_MAP("monotonic", CLOCK_MONOTONIC),
	CLOCKID_MAP("monotonic_raw", CLOCK_MONOTONIC_RAW),

	/* available क्रम some events */
	CLOCKID_MAP("realtime", CLOCK_REALTIME),
	CLOCKID_MAP("boottime", CLOCK_BOOTTIME),
	CLOCKID_MAP("tai", CLOCK_TAI),

	/* available क्रम the lazy */
	CLOCKID_MAP("mono", CLOCK_MONOTONIC),
	CLOCKID_MAP("raw", CLOCK_MONOTONIC_RAW),
	CLOCKID_MAP("real", CLOCK_REALTIME),
	CLOCKID_MAP("boot", CLOCK_BOOTTIME),

	CLOCKID_END,
पूर्ण;

अटल पूर्णांक get_घड़ीid_res(घड़ीid_t clk_id, u64 *res_ns)
अणु
	काष्ठा बारpec res;

	*res_ns = 0;
	अगर (!घड़ी_getres(clk_id, &res))
		*res_ns = res.tv_nsec + res.tv_sec * NSEC_PER_SEC;
	अन्यथा
		pr_warning("WARNING: Failed to determine specified clock resolution.\n");

	वापस 0;
पूर्ण

पूर्णांक parse_घड़ीid(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset)
अणु
	काष्ठा record_opts *opts = (काष्ठा record_opts *)opt->value;
	स्थिर काष्ठा घड़ीid_map *cm;
	स्थिर अक्षर *ostr = str;

	अगर (unset) अणु
		opts->use_घड़ीid = 0;
		वापस 0;
	पूर्ण

	/* no arg passed */
	अगर (!str)
		वापस 0;

	/* no setting it twice */
	अगर (opts->use_घड़ीid)
		वापस -1;

	opts->use_घड़ीid = true;

	/* अगर its a number, we're करोne */
	अगर (माला_पूछो(str, "%d", &opts->घड़ीid) == 1)
		वापस get_घड़ीid_res(opts->घड़ीid, &opts->घड़ीid_res_ns);

	/* allow a "CLOCK_" prefix to the name */
	अगर (!strnहालcmp(str, "CLOCK_", 6))
		str += 6;

	क्रम (cm = घड़ीids; cm->name; cm++) अणु
		अगर (!strहालcmp(str, cm->name)) अणु
			opts->घड़ीid = cm->घड़ीid;
			वापस get_घड़ीid_res(opts->घड़ीid,
					       &opts->घड़ीid_res_ns);
		पूर्ण
	पूर्ण

	opts->use_घड़ीid = false;
	ui__warning("unknown clockid %s, check man page\n", ostr);
	वापस -1;
पूर्ण

स्थिर अक्षर *घड़ीid_name(घड़ीid_t clk_id)
अणु
	स्थिर काष्ठा घड़ीid_map *cm;

	क्रम (cm = घड़ीids; cm->name; cm++) अणु
		अगर (cm->घड़ीid == clk_id)
			वापस cm->name;
	पूर्ण
	वापस "(not found)";
पूर्ण
