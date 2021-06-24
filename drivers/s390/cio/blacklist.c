<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *   S/390 common I/O routines -- blacklisting of specअगरic devices
 *
 *    Copyright IBM Corp. 1999, 2013
 *    Author(s): Ingo Adlung (adlung@de.ibm.com)
 *		 Cornelia Huck (cornelia.huck@de.ibm.com)
 *		 Arnd Bergmann (arndb@de.ibm.com)
 */

#घोषणा KMSG_COMPONENT "cio"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/device.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/ipl.h>

#समावेश "blacklist.h"
#समावेश "cio.h"
#समावेश "cio_debug.h"
#समावेश "css.h"
#समावेश "device.h"

/*
 * "Blacklisting" of certain devices:
 * Device numbers given in the commandline as cio_ignore=... won't be known
 * to Linux.
 *
 * These can be single devices or ranges of devices
 */

/* 65536 bits क्रम each set to indicate अगर a devno is blacklisted or not */
#घोषणा __BL_DEV_WORDS ((__MAX_SUBCHANNEL + (8*माप(दीर्घ) - 1)) / \
			 (8*माप(दीर्घ)))
अटल अचिन्हित दीर्घ bl_dev[__MAX_SSID + 1][__BL_DEV_WORDS];
प्रकार क्रमागत अणुadd, मुक्तपूर्ण range_action;

/*
 * Function: blacklist_range
 * (Un-)blacklist the devices from-to
 */
अटल पूर्णांक blacklist_range(range_action action, अचिन्हित पूर्णांक from_ssid,
			   अचिन्हित पूर्णांक to_ssid, अचिन्हित पूर्णांक from,
			   अचिन्हित पूर्णांक to, पूर्णांक msgtrigger)
अणु
	अगर ((from_ssid > to_ssid) || ((from_ssid == to_ssid) && (from > to))) अणु
		अगर (msgtrigger)
			pr_warn("0.%x.%04x to 0.%x.%04x is not a valid range for cio_ignore\n",
				from_ssid, from, to_ssid, to);

		वापस 1;
	पूर्ण

	जबतक ((from_ssid < to_ssid) || ((from_ssid == to_ssid) &&
	       (from <= to))) अणु
		अगर (action == add)
			set_bit(from, bl_dev[from_ssid]);
		अन्यथा
			clear_bit(from, bl_dev[from_ssid]);
		from++;
		अगर (from > __MAX_SUBCHANNEL) अणु
			from_ssid++;
			from = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pure_hex(अक्षर **cp, अचिन्हित पूर्णांक *val, पूर्णांक min_digit,
		    पूर्णांक max_digit, पूर्णांक max_val)
अणु
	पूर्णांक dअगरf;

	dअगरf = 0;
	*val = 0;

	जबतक (dअगरf <= max_digit) अणु
		पूर्णांक value = hex_to_bin(**cp);

		अगर (value < 0)
			अवरोध;
		*val = *val * 16 + value;
		(*cp)++;
		dअगरf++;
	पूर्ण

	अगर ((dअगरf < min_digit) || (dअगरf > max_digit) || (*val > max_val))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक parse_busid(अक्षर *str, अचिन्हित पूर्णांक *cssid, अचिन्हित पूर्णांक *ssid,
		       अचिन्हित पूर्णांक *devno, पूर्णांक msgtrigger)
अणु
	अक्षर *str_work;
	पूर्णांक val, rc, ret;

	rc = 1;

	अगर (*str == '\0')
		जाओ out;

	/* old style */
	str_work = str;
	val = simple_म_से_अदीर्घ(str, &str_work, 16);

	अगर (*str_work == '\0') अणु
		अगर (val <= __MAX_SUBCHANNEL) अणु
			*devno = val;
			*ssid = 0;
			*cssid = 0;
			rc = 0;
		पूर्ण
		जाओ out;
	पूर्ण

	/* new style */
	str_work = str;
	ret = pure_hex(&str_work, cssid, 1, 2, __MAX_CSSID);
	अगर (ret || (str_work[0] != '.'))
		जाओ out;
	str_work++;
	ret = pure_hex(&str_work, ssid, 1, 1, __MAX_SSID);
	अगर (ret || (str_work[0] != '.'))
		जाओ out;
	str_work++;
	ret = pure_hex(&str_work, devno, 4, 4, __MAX_SUBCHANNEL);
	अगर (ret || (str_work[0] != '\0'))
		जाओ out;

	rc = 0;
out:
	अगर (rc && msgtrigger)
		pr_warn("%s is not a valid device for the cio_ignore kernel parameter\n",
			str);

	वापस rc;
पूर्ण

अटल पूर्णांक blacklist_parse_parameters(अक्षर *str, range_action action,
				      पूर्णांक msgtrigger)
अणु
	अचिन्हित पूर्णांक from_cssid, to_cssid, from_ssid, to_ssid, from, to;
	पूर्णांक rc, totalrc;
	अक्षर *parm;
	range_action ra;

	totalrc = 0;

	जबतक ((parm = strsep(&str, ","))) अणु
		rc = 0;
		ra = action;
		अगर (*parm == '!') अणु
			अगर (ra == add)
				ra = मुक्त;
			अन्यथा
				ra = add;
			parm++;
		पूर्ण
		अगर (म_भेद(parm, "all") == 0) अणु
			from_cssid = 0;
			from_ssid = 0;
			from = 0;
			to_cssid = __MAX_CSSID;
			to_ssid = __MAX_SSID;
			to = __MAX_SUBCHANNEL;
		पूर्ण अन्यथा अगर (म_भेद(parm, "ipldev") == 0) अणु
			अगर (ipl_info.type == IPL_TYPE_CCW) अणु
				from_cssid = 0;
				from_ssid = ipl_info.data.ccw.dev_id.ssid;
				from = ipl_info.data.ccw.dev_id.devno;
			पूर्ण अन्यथा अगर (ipl_info.type == IPL_TYPE_FCP ||
				   ipl_info.type == IPL_TYPE_FCP_DUMP) अणु
				from_cssid = 0;
				from_ssid = ipl_info.data.fcp.dev_id.ssid;
				from = ipl_info.data.fcp.dev_id.devno;
			पूर्ण अन्यथा अणु
				जारी;
			पूर्ण
			to_cssid = from_cssid;
			to_ssid = from_ssid;
			to = from;
		पूर्ण अन्यथा अगर (म_भेद(parm, "condev") == 0) अणु
			अगर (console_devno == -1)
				जारी;

			from_cssid = to_cssid = 0;
			from_ssid = to_ssid = 0;
			from = to = console_devno;
		पूर्ण अन्यथा अणु
			rc = parse_busid(strsep(&parm, "-"), &from_cssid,
					 &from_ssid, &from, msgtrigger);
			अगर (!rc) अणु
				अगर (parm != शून्य)
					rc = parse_busid(parm, &to_cssid,
							 &to_ssid, &to,
							 msgtrigger);
				अन्यथा अणु
					to_cssid = from_cssid;
					to_ssid = from_ssid;
					to = from;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (!rc) अणु
			rc = blacklist_range(ra, from_ssid, to_ssid, from, to,
					     msgtrigger);
			अगर (rc)
				totalrc = -EINVAL;
		पूर्ण अन्यथा
			totalrc = -EINVAL;
	पूर्ण

	वापस totalrc;
पूर्ण

अटल पूर्णांक __init
blacklist_setup (अक्षर *str)
अणु
	CIO_MSG_EVENT(6, "Reading blacklist parameters\n");
	अगर (blacklist_parse_parameters(str, add, 1))
		वापस 0;
	वापस 1;
पूर्ण

__setup ("cio_ignore=", blacklist_setup);

/* Checking अगर devices are blacklisted */

/*
 * Function: is_blacklisted
 * Returns 1 अगर the given devicक्रमागतber can be found in the blacklist,
 * otherwise 0.
 * Used by validate_subchannel()
 */
पूर्णांक
is_blacklisted (पूर्णांक ssid, पूर्णांक devno)
अणु
	वापस test_bit (devno, bl_dev[ssid]);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
/*
 * Function: blacklist_parse_proc_parameters
 * parse the stuff which is piped to /proc/cio_ignore
 */
अटल पूर्णांक blacklist_parse_proc_parameters(अक्षर *buf)
अणु
	पूर्णांक rc;
	अक्षर *parm;

	parm = strsep(&buf, " ");

	अगर (म_भेद("free", parm) == 0) अणु
		rc = blacklist_parse_parameters(buf, मुक्त, 0);
		css_schedule_eval_all_unreg(0);
	पूर्ण अन्यथा अगर (म_भेद("add", parm) == 0)
		rc = blacklist_parse_parameters(buf, add, 0);
	अन्यथा अगर (म_भेद("purge", parm) == 0)
		वापस ccw_purge_blacklisted();
	अन्यथा
		वापस -EINVAL;


	वापस rc;
पूर्ण

/* Iterator काष्ठा क्रम all devices. */
काष्ठा ccwdev_iter अणु
	पूर्णांक devno;
	पूर्णांक ssid;
	पूर्णांक in_range;
पूर्ण;

अटल व्योम *
cio_ignore_proc_seq_start(काष्ठा seq_file *s, loff_t *offset)
अणु
	काष्ठा ccwdev_iter *iter = s->निजी;

	अगर (*offset >= (__MAX_SUBCHANNEL + 1) * (__MAX_SSID + 1))
		वापस शून्य;
	स_रखो(iter, 0, माप(*iter));
	iter->ssid = *offset / (__MAX_SUBCHANNEL + 1);
	iter->devno = *offset % (__MAX_SUBCHANNEL + 1);
	वापस iter;
पूर्ण

अटल व्योम
cio_ignore_proc_seq_stop(काष्ठा seq_file *s, व्योम *it)
अणु
पूर्ण

अटल व्योम *
cio_ignore_proc_seq_next(काष्ठा seq_file *s, व्योम *it, loff_t *offset)
अणु
	काष्ठा ccwdev_iter *iter;
	loff_t p = *offset;

	(*offset)++;
	अगर (p >= (__MAX_SUBCHANNEL + 1) * (__MAX_SSID + 1))
		वापस शून्य;
	iter = it;
	अगर (iter->devno == __MAX_SUBCHANNEL) अणु
		iter->devno = 0;
		iter->ssid++;
		अगर (iter->ssid > __MAX_SSID)
			वापस शून्य;
	पूर्ण अन्यथा
		iter->devno++;
	वापस iter;
पूर्ण

अटल पूर्णांक
cio_ignore_proc_seq_show(काष्ठा seq_file *s, व्योम *it)
अणु
	काष्ठा ccwdev_iter *iter;

	iter = it;
	अगर (!is_blacklisted(iter->ssid, iter->devno))
		/* Not blacklisted, nothing to output. */
		वापस 0;
	अगर (!iter->in_range) अणु
		/* First device in range. */
		अगर ((iter->devno == __MAX_SUBCHANNEL) ||
		    !is_blacklisted(iter->ssid, iter->devno + 1)) अणु
			/* Singular device. */
			seq_म_लिखो(s, "0.%x.%04x\n", iter->ssid, iter->devno);
			वापस 0;
		पूर्ण
		iter->in_range = 1;
		seq_म_लिखो(s, "0.%x.%04x-", iter->ssid, iter->devno);
		वापस 0;
	पूर्ण
	अगर ((iter->devno == __MAX_SUBCHANNEL) ||
	    !is_blacklisted(iter->ssid, iter->devno + 1)) अणु
		/* Last device in range. */
		iter->in_range = 0;
		seq_म_लिखो(s, "0.%x.%04x\n", iter->ssid, iter->devno);
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
cio_ignore_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
		 माप_प्रकार user_len, loff_t *offset)
अणु
	अक्षर *buf;
	sमाप_प्रकार rc, ret, i;

	अगर (*offset)
		वापस -EINVAL;
	अगर (user_len > 65536)
		user_len = 65536;
	buf = vzalloc(user_len + 1); /* maybe better use the stack? */
	अगर (buf == शून्य)
		वापस -ENOMEM;

	अगर (म_नकलन_from_user (buf, user_buf, user_len) < 0) अणु
		rc = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	i = user_len - 1;
	जबतक ((i >= 0) && (है_खाली(buf[i]) || (buf[i] == 0))) अणु
		buf[i] = '\0';
		i--;
	पूर्ण
	ret = blacklist_parse_proc_parameters(buf);
	अगर (ret)
		rc = ret;
	अन्यथा
		rc = user_len;

out_मुक्त:
	vमुक्त (buf);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा seq_operations cio_ignore_proc_seq_ops = अणु
	.start = cio_ignore_proc_seq_start,
	.stop  = cio_ignore_proc_seq_stop,
	.next  = cio_ignore_proc_seq_next,
	.show  = cio_ignore_proc_seq_show,
पूर्ण;

अटल पूर्णांक
cio_ignore_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो_निजी(file, &cio_ignore_proc_seq_ops,
				माप(काष्ठा ccwdev_iter));
पूर्ण

अटल स्थिर काष्ठा proc_ops cio_ignore_proc_ops = अणु
	.proc_खोलो	= cio_ignore_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= seq_release_निजी,
	.proc_ग_लिखो	= cio_ignore_ग_लिखो,
पूर्ण;

अटल पूर्णांक
cio_ignore_proc_init (व्योम)
अणु
	काष्ठा proc_dir_entry *entry;

	entry = proc_create("cio_ignore", S_IFREG | S_IRUGO | S_IWUSR, शून्य,
			    &cio_ignore_proc_ops);
	अगर (!entry)
		वापस -ENOENT;
	वापस 0;
पूर्ण

__initcall (cio_ignore_proc_init);

#पूर्ण_अगर /* CONFIG_PROC_FS */
