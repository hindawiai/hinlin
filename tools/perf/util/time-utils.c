<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/माला.स>
#समावेश <sys/समय.स>
#समावेश <linux/समय64.h>
#समावेश <समय.स>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <गणित.स>
#समावेश <linux/प्रकार.स>

#समावेश "debug.h"
#समावेश "time-utils.h"
#समावेश "session.h"
#समावेश "evlist.h"

पूर्णांक parse_nsec_समय(स्थिर अक्षर *str, u64 *pसमय)
अणु
	u64 समय_sec, समय_nsec;
	अक्षर *end;

	समय_sec = म_से_अदीर्घ(str, &end, 10);
	अगर (*end != '.' && *end != '\0')
		वापस -1;

	अगर (*end == '.') अणु
		पूर्णांक i;
		अक्षर nsec_buf[10];

		अगर (म_माप(++end) > 9)
			वापस -1;

		म_नकलन(nsec_buf, end, 9);
		nsec_buf[9] = '\0';

		/* make it nsec precision */
		क्रम (i = म_माप(nsec_buf); i < 9; i++)
			nsec_buf[i] = '0';

		समय_nsec = म_से_अदीर्घ(nsec_buf, &end, 10);
		अगर (*end != '\0')
			वापस -1;
	पूर्ण अन्यथा
		समय_nsec = 0;

	*pसमय = समय_sec * NSEC_PER_SEC + समय_nsec;
	वापस 0;
पूर्ण

अटल पूर्णांक parse_बारtr_sec_nsec(काष्ठा perf_समय_पूर्णांकerval *pसमय,
				  अक्षर *start_str, अक्षर *end_str)
अणु
	अगर (start_str && (*start_str != '\0') &&
	    (parse_nsec_समय(start_str, &pसमय->start) != 0)) अणु
		वापस -1;
	पूर्ण

	अगर (end_str && (*end_str != '\0') &&
	    (parse_nsec_समय(end_str, &pसमय->end) != 0)) अणु
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक split_start_end(अक्षर **start, अक्षर **end, स्थिर अक्षर *ostr, अक्षर ch)
अणु
	अक्षर *start_str, *end_str;
	अक्षर *d, *str;

	अगर (ostr == शून्य || *ostr == '\0')
		वापस 0;

	/* copy original string because we need to modअगरy it */
	str = strdup(ostr);
	अगर (str == शून्य)
		वापस -ENOMEM;

	start_str = str;
	d = म_अक्षर(start_str, ch);
	अगर (d) अणु
		*d = '\0';
		++d;
	पूर्ण
	end_str = d;

	*start = start_str;
	*end = end_str;

	वापस 0;
पूर्ण

पूर्णांक perf_समय__parse_str(काष्ठा perf_समय_पूर्णांकerval *pसमय, स्थिर अक्षर *ostr)
अणु
	अक्षर *start_str = शून्य, *end_str;
	पूर्णांक rc;

	rc = split_start_end(&start_str, &end_str, ostr, ',');
	अगर (rc || !start_str)
		वापस rc;

	pसमय->start = 0;
	pसमय->end = 0;

	rc = parse_बारtr_sec_nsec(pसमय, start_str, end_str);

	मुक्त(start_str);

	/* make sure end समय is after start समय अगर it was given */
	अगर (rc == 0 && pसमय->end && pसमय->end < pसमय->start)
		वापस -EINVAL;

	pr_debug("start time %" PRIu64 ", ", pसमय->start);
	pr_debug("end time %" PRIu64 "\n", pसमय->end);

	वापस rc;
पूर्ण

अटल पूर्णांक perf_समय__parse_strs(काष्ठा perf_समय_पूर्णांकerval *pसमय,
				 स्थिर अक्षर *ostr, पूर्णांक size)
अणु
	स्थिर अक्षर *cp;
	अक्षर *str, *arg, *p;
	पूर्णांक i, num = 0, rc = 0;

	/* Count the commas */
	क्रम (cp = ostr; *cp; cp++)
		num += !!(*cp == ',');

	अगर (!num)
		वापस -EINVAL;

	BUG_ON(num > size);

	str = strdup(ostr);
	अगर (!str)
		वापस -ENOMEM;

	/* Split the string and parse each piece, except the last */
	क्रम (i = 0, p = str; i < num - 1; i++) अणु
		arg = p;
		/* Find next comma, there must be one */
		p = skip_spaces(म_अक्षर(p, ',') + 1);
		/* Skip the value, must not contain space or comma */
		जबतक (*p && !है_खाली(*p)) अणु
			अगर (*p++ == ',') अणु
				rc = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
		/* Split and parse */
		अगर (*p)
			*p++ = 0;
		rc = perf_समय__parse_str(pसमय + i, arg);
		अगर (rc < 0)
			जाओ out;
	पूर्ण

	/* Parse the last piece */
	rc = perf_समय__parse_str(pसमय + i, p);
	अगर (rc < 0)
		जाओ out;

	/* Check there is no overlap */
	क्रम (i = 0; i < num - 1; i++) अणु
		अगर (pसमय[i].end >= pसमय[i + 1].start) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	rc = num;
out:
	मुक्त(str);

	वापस rc;
पूर्ण

अटल पूर्णांक parse_percent(द्विगुन *pcnt, अक्षर *str)
अणु
	अक्षर *c, *endptr;
	द्विगुन d;

	c = म_अक्षर(str, '%');
	अगर (c)
		*c = '\0';
	अन्यथा
		वापस -1;

	d = म_से_भग्न(str, &endptr);
	अगर (endptr != str + म_माप(str))
		वापस -1;

	*pcnt = d / 100.0;
	वापस 0;
पूर्ण

अटल पूर्णांक set_percent_समय(काष्ठा perf_समय_पूर्णांकerval *pसमय, द्विगुन start_pcnt,
			    द्विगुन end_pcnt, u64 start, u64 end)
अणु
	u64 total = end - start;

	अगर (start_pcnt < 0.0 || start_pcnt > 1.0 ||
	    end_pcnt < 0.0 || end_pcnt > 1.0) अणु
		वापस -1;
	पूर्ण

	pसमय->start = start + round(start_pcnt * total);
	pसमय->end = start + round(end_pcnt * total);

	अगर (pसमय->end > pसमय->start && pसमय->end != end)
		pसमय->end -= 1;

	वापस 0;
पूर्ण

अटल पूर्णांक percent_slash_split(अक्षर *str, काष्ठा perf_समय_पूर्णांकerval *pसमय,
			       u64 start, u64 end)
अणु
	अक्षर *p, *end_str;
	द्विगुन pcnt, start_pcnt, end_pcnt;
	पूर्णांक i;

	/*
	 * Example:
	 * 10%/2: select the second 10% slice and the third 10% slice
	 */

	/* We can modअगरy this string since the original one is copied */
	p = म_अक्षर(str, '/');
	अगर (!p)
		वापस -1;

	*p = '\0';
	अगर (parse_percent(&pcnt, str) < 0)
		वापस -1;

	p++;
	i = (पूर्णांक)म_से_दीर्घ(p, &end_str, 10);
	अगर (*end_str)
		वापस -1;

	अगर (pcnt <= 0.0)
		वापस -1;

	start_pcnt = pcnt * (i - 1);
	end_pcnt = pcnt * i;

	वापस set_percent_समय(pसमय, start_pcnt, end_pcnt, start, end);
पूर्ण

अटल पूर्णांक percent_dash_split(अक्षर *str, काष्ठा perf_समय_पूर्णांकerval *pसमय,
			      u64 start, u64 end)
अणु
	अक्षर *start_str = शून्य, *end_str;
	द्विगुन start_pcnt, end_pcnt;
	पूर्णांक ret;

	/*
	 * Example: 0%-10%
	 */

	ret = split_start_end(&start_str, &end_str, str, '-');
	अगर (ret || !start_str)
		वापस ret;

	अगर ((parse_percent(&start_pcnt, start_str) != 0) ||
	    (parse_percent(&end_pcnt, end_str) != 0)) अणु
		मुक्त(start_str);
		वापस -1;
	पूर्ण

	मुक्त(start_str);

	वापस set_percent_समय(pसमय, start_pcnt, end_pcnt, start, end);
पूर्ण

प्रकार पूर्णांक (*समय_pecent_split)(अक्षर *, काष्ठा perf_समय_पूर्णांकerval *,
				 u64 start, u64 end);

अटल पूर्णांक percent_comma_split(काष्ठा perf_समय_पूर्णांकerval *pसमय_buf, पूर्णांक num,
			       स्थिर अक्षर *ostr, u64 start, u64 end,
			       समय_pecent_split func)
अणु
	अक्षर *str, *p1, *p2;
	पूर्णांक len, ret, i = 0;

	str = strdup(ostr);
	अगर (str == शून्य)
		वापस -ENOMEM;

	len = म_माप(str);
	p1 = str;

	जबतक (p1 < str + len) अणु
		अगर (i >= num) अणु
			मुक्त(str);
			वापस -1;
		पूर्ण

		p2 = म_अक्षर(p1, ',');
		अगर (p2)
			*p2 = '\0';

		ret = (func)(p1, &pसमय_buf[i], start, end);
		अगर (ret < 0) अणु
			मुक्त(str);
			वापस -1;
		पूर्ण

		pr_debug("start time %d: %" PRIu64 ", ", i, pसमय_buf[i].start);
		pr_debug("end time %d: %" PRIu64 "\n", i, pसमय_buf[i].end);

		i++;

		अगर (p2)
			p1 = p2 + 1;
		अन्यथा
			अवरोध;
	पूर्ण

	मुक्त(str);
	वापस i;
पूर्ण

अटल पूर्णांक one_percent_convert(काष्ठा perf_समय_पूर्णांकerval *pसमय_buf,
			       स्थिर अक्षर *ostr, u64 start, u64 end, अक्षर *c)
अणु
	अक्षर *str;
	पूर्णांक len = म_माप(ostr), ret;

	/*
	 * c poपूर्णांकs to '%'.
	 * '%' should be the last अक्षरacter
	 */
	अगर (ostr + len - 1 != c)
		वापस -1;

	/*
	 * Conकाष्ठा a string like "xx%/1"
	 */
	str = दो_स्मृति(len + 3);
	अगर (str == शून्य)
		वापस -ENOMEM;

	स_नकल(str, ostr, len);
	म_नकल(str + len, "/1");

	ret = percent_slash_split(str, pसमय_buf, start, end);
	अगर (ret == 0)
		ret = 1;

	मुक्त(str);
	वापस ret;
पूर्ण

पूर्णांक perf_समय__percent_parse_str(काष्ठा perf_समय_पूर्णांकerval *pसमय_buf, पूर्णांक num,
				 स्थिर अक्षर *ostr, u64 start, u64 end)
अणु
	अक्षर *c;

	/*
	 * ostr example:
	 * 10%/2,10%/3: select the second 10% slice and the third 10% slice
	 * 0%-10%,30%-40%: multiple समय range
	 * 50%: just one percent
	 */

	स_रखो(pसमय_buf, 0, माप(*pसमय_buf) * num);

	c = म_अक्षर(ostr, '/');
	अगर (c) अणु
		वापस percent_comma_split(pसमय_buf, num, ostr, start,
					   end, percent_slash_split);
	पूर्ण

	c = म_अक्षर(ostr, '-');
	अगर (c) अणु
		वापस percent_comma_split(pसमय_buf, num, ostr, start,
					   end, percent_dash_split);
	पूर्ण

	c = म_अक्षर(ostr, '%');
	अगर (c)
		वापस one_percent_convert(pसमय_buf, ostr, start, end, c);

	वापस -1;
पूर्ण

काष्ठा perf_समय_पूर्णांकerval *perf_समय__range_alloc(स्थिर अक्षर *ostr, पूर्णांक *size)
अणु
	स्थिर अक्षर *p1, *p2;
	पूर्णांक i = 1;
	काष्ठा perf_समय_पूर्णांकerval *pसमय;

	/*
	 * At least allocate one समय range.
	 */
	अगर (!ostr)
		जाओ alloc;

	p1 = ostr;
	जबतक (p1 < ostr + म_माप(ostr)) अणु
		p2 = म_अक्षर(p1, ',');
		अगर (!p2)
			अवरोध;

		p1 = p2 + 1;
		i++;
	पूर्ण

alloc:
	*size = i;
	pसमय = सुस्मृति(i, माप(*pसमय));
	वापस pसमय;
पूर्ण

bool perf_समय__skip_sample(काष्ठा perf_समय_पूर्णांकerval *pसमय, u64 बारtamp)
अणु
	/* अगर समय is not set करोn't drop sample */
	अगर (बारtamp == 0)
		वापस false;

	/* otherwise compare sample समय to समय winकरोw */
	अगर ((pसमय->start && बारtamp < pसमय->start) ||
	    (pसमय->end && बारtamp > pसमय->end)) अणु
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool perf_समय__ranges_skip_sample(काष्ठा perf_समय_पूर्णांकerval *pसमय_buf,
				   पूर्णांक num, u64 बारtamp)
अणु
	काष्ठा perf_समय_पूर्णांकerval *pसमय;
	पूर्णांक i;

	अगर ((!pसमय_buf) || (बारtamp == 0) || (num == 0))
		वापस false;

	अगर (num == 1)
		वापस perf_समय__skip_sample(&pसमय_buf[0], बारtamp);

	/*
	 * start/end of multiple समय ranges must be valid.
	 */
	क्रम (i = 0; i < num; i++) अणु
		pसमय = &pसमय_buf[i];

		अगर (बारtamp >= pसमय->start &&
		    (बारtamp <= pसमय->end || !pसमय->end)) अणु
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक perf_समय__parse_क्रम_ranges_relसमय(स्थिर अक्षर *समय_str,
				काष्ठा perf_session *session,
				काष्ठा perf_समय_पूर्णांकerval **ranges,
				पूर्णांक *range_size, पूर्णांक *range_num,
				bool relसमय)
अणु
	bool has_percent = म_अक्षर(समय_str, '%');
	काष्ठा perf_समय_पूर्णांकerval *pसमय_range;
	पूर्णांक size, num, ret = -EINVAL;

	pसमय_range = perf_समय__range_alloc(समय_str, &size);
	अगर (!pसमय_range)
		वापस -ENOMEM;

	अगर (has_percent || relसमय) अणु
		अगर (session->evlist->first_sample_समय == 0 &&
		    session->evlist->last_sample_समय == 0) अणु
			pr_err("HINT: no first/last sample time found in perf data.\n"
			       "Please use latest perf binary to execute 'perf record'\n"
			       "(if '--buildid-all' is enabled, please set '--timestamp-boundary').\n");
			जाओ error;
		पूर्ण
	पूर्ण

	अगर (has_percent) अणु
		num = perf_समय__percent_parse_str(
				pसमय_range, size,
				समय_str,
				session->evlist->first_sample_समय,
				session->evlist->last_sample_समय);
	पूर्ण अन्यथा अणु
		num = perf_समय__parse_strs(pसमय_range, समय_str, size);
	पूर्ण

	अगर (num < 0)
		जाओ error_invalid;

	अगर (relसमय) अणु
		पूर्णांक i;

		क्रम (i = 0; i < num; i++) अणु
			pसमय_range[i].start += session->evlist->first_sample_समय;
			pसमय_range[i].end += session->evlist->first_sample_समय;
		पूर्ण
	पूर्ण

	*range_size = size;
	*range_num = num;
	*ranges = pसमय_range;
	वापस 0;

error_invalid:
	pr_err("Invalid time string\n");
error:
	मुक्त(pसमय_range);
	वापस ret;
पूर्ण

पूर्णांक perf_समय__parse_क्रम_ranges(स्थिर अक्षर *समय_str,
				काष्ठा perf_session *session,
				काष्ठा perf_समय_पूर्णांकerval **ranges,
				पूर्णांक *range_size, पूर्णांक *range_num)
अणु
	वापस perf_समय__parse_क्रम_ranges_relसमय(समय_str, session, ranges,
					range_size, range_num, false);
पूर्ण

पूर्णांक बारtamp__scnम_लिखो_usec(u64 बारtamp, अक्षर *buf, माप_प्रकार sz)
अणु
	u64  sec = बारtamp / NSEC_PER_SEC;
	u64 usec = (बारtamp % NSEC_PER_SEC) / NSEC_PER_USEC;

	वापस scnम_लिखो(buf, sz, "%"PRIu64".%06"PRIu64, sec, usec);
पूर्ण

पूर्णांक बारtamp__scnम_लिखो_nsec(u64 बारtamp, अक्षर *buf, माप_प्रकार sz)
अणु
	u64 sec  = बारtamp / NSEC_PER_SEC,
	    nsec = बारtamp % NSEC_PER_SEC;

	वापस scnम_लिखो(buf, sz, "%" PRIu64 ".%09" PRIu64, sec, nsec);
पूर्ण

पूर्णांक fetch_current_बारtamp(अक्षर *buf, माप_प्रकार sz)
अणु
	काष्ठा समयval tv;
	काष्ठा पंचांग पंचांग;
	अक्षर dt[32];

	अगर (समय_लोofday(&tv, शून्य) || !स_स्थानीय_r(&tv.tv_sec, &पंचांग))
		वापस -1;

	अगर (!स_माला(dt, माप(dt), "%Y%m%d%H%M%S", &पंचांग))
		वापस -1;

	scnम_लिखो(buf, sz, "%s%02u", dt, (अचिन्हित)tv.tv_usec / 10000);

	वापस 0;
पूर्ण
