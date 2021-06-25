<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005,2006,2007,2008 IBM Corporation
 *
 * Authors:
 * Kylene Hall <kjhall@us.ibm.com>
 * Reiner Sailer <sailer@us.ibm.com>
 * Mimi Zohar <zohar@us.ibm.com>
 *
 * File: ima_fs.c
 *	implemenents security file प्रणाली क्रम reporting
 *	current measurement list and IMA statistics
 */

#समावेश <linux/fcntl.h>
#समावेश <linux/kernel_पढ़ो_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/parser.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "ima.h"

अटल DEFINE_MUTEX(ima_ग_लिखो_mutex);

bool ima_canonical_fmt;
अटल पूर्णांक __init शेष_canonical_fmt_setup(अक्षर *str)
अणु
#अगर_घोषित __BIG_ENDIAN
	ima_canonical_fmt = true;
#पूर्ण_अगर
	वापस 1;
पूर्ण
__setup("ima_canonical_fmt", शेष_canonical_fmt_setup);

अटल पूर्णांक valid_policy = 1;

अटल sमाप_प्रकार ima_show_htable_value(अक्षर __user *buf, माप_प्रकार count,
				     loff_t *ppos, atomic_दीर्घ_t *val)
अणु
	अक्षर पंचांगpbuf[32];	/* greater than largest 'long' string value */
	sमाप_प्रकार len;

	len = scnम_लिखो(पंचांगpbuf, माप(पंचांगpbuf), "%li\n", atomic_दीर्घ_पढ़ो(val));
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगpbuf, len);
पूर्ण

अटल sमाप_प्रकार ima_show_htable_violations(काष्ठा file *filp,
					  अक्षर __user *buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	वापस ima_show_htable_value(buf, count, ppos, &ima_htable.violations);
पूर्ण

अटल स्थिर काष्ठा file_operations ima_htable_violations_ops = अणु
	.पढ़ो = ima_show_htable_violations,
	.llseek = generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार ima_show_measurements_count(काष्ठा file *filp,
					   अक्षर __user *buf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	वापस ima_show_htable_value(buf, count, ppos, &ima_htable.len);

पूर्ण

अटल स्थिर काष्ठा file_operations ima_measurements_count_ops = अणु
	.पढ़ो = ima_show_measurements_count,
	.llseek = generic_file_llseek,
पूर्ण;

/* वापसs poपूर्णांकer to hlist_node */
अटल व्योम *ima_measurements_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	loff_t l = *pos;
	काष्ठा ima_queue_entry *qe;

	/* we need a lock since pos could poपूर्णांक beyond last element */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(qe, &ima_measurements, later) अणु
		अगर (!l--) अणु
			rcu_पढ़ो_unlock();
			वापस qe;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस शून्य;
पूर्ण

अटल व्योम *ima_measurements_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा ima_queue_entry *qe = v;

	/* lock protects when पढ़ोing beyond last element
	 * against concurrent list-extension
	 */
	rcu_पढ़ो_lock();
	qe = list_entry_rcu(qe->later.next, काष्ठा ima_queue_entry, later);
	rcu_पढ़ो_unlock();
	(*pos)++;

	वापस (&qe->later == &ima_measurements) ? शून्य : qe;
पूर्ण

अटल व्योम ima_measurements_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

व्योम ima_अ_दो(काष्ठा seq_file *m, व्योम *data, पूर्णांक datalen)
अणु
	जबतक (datalen--)
		seq_अ_दो(m, *(अक्षर *)data++);
पूर्ण

/* prपूर्णांक क्रमmat:
 *       32bit-le=pcr#
 *       अक्षर[20]=ढाँचा digest
 *       32bit-le=ढाँचा name size
 *       अक्षर[n]=ढाँचा name
 *       [eventdata length]
 *       eventdata[n]=ढाँचा specअगरic data
 */
पूर्णांक ima_measurements_show(काष्ठा seq_file *m, व्योम *v)
अणु
	/* the list never shrinks, so we करोn't need a lock here */
	काष्ठा ima_queue_entry *qe = v;
	काष्ठा ima_ढाँचा_entry *e;
	अक्षर *ढाँचा_name;
	u32 pcr, namelen, ढाँचा_data_len; /* temporary fields */
	bool is_ima_ढाँचा = false;
	पूर्णांक i;

	/* get entry */
	e = qe->entry;
	अगर (e == शून्य)
		वापस -1;

	ढाँचा_name = (e->ढाँचा_desc->name[0] != '\0') ?
	    e->ढाँचा_desc->name : e->ढाँचा_desc->fmt;

	/*
	 * 1st: PCRIndex
	 * PCR used शेषs to the same (config option) in
	 * little-endian क्रमmat, unless set in policy
	 */
	pcr = !ima_canonical_fmt ? e->pcr : cpu_to_le32(e->pcr);
	ima_अ_दो(m, &pcr, माप(e->pcr));

	/* 2nd: ढाँचा digest */
	ima_अ_दो(m, e->digests[ima_sha1_idx].digest, TPM_DIGEST_SIZE);

	/* 3rd: ढाँचा name size */
	namelen = !ima_canonical_fmt ? म_माप(ढाँचा_name) :
		cpu_to_le32(म_माप(ढाँचा_name));
	ima_अ_दो(m, &namelen, माप(namelen));

	/* 4th:  ढाँचा name */
	ima_अ_दो(m, ढाँचा_name, म_माप(ढाँचा_name));

	/* 5th:  ढाँचा length (except क्रम 'ima' ढाँचा) */
	अगर (म_भेद(ढाँचा_name, IMA_TEMPLATE_IMA_NAME) == 0)
		is_ima_ढाँचा = true;

	अगर (!is_ima_ढाँचा) अणु
		ढाँचा_data_len = !ima_canonical_fmt ? e->ढाँचा_data_len :
			cpu_to_le32(e->ढाँचा_data_len);
		ima_अ_दो(m, &ढाँचा_data_len, माप(e->ढाँचा_data_len));
	पूर्ण

	/* 6th:  ढाँचा specअगरic data */
	क्रम (i = 0; i < e->ढाँचा_desc->num_fields; i++) अणु
		क्रमागत ima_show_type show = IMA_SHOW_BINARY;
		स्थिर काष्ठा ima_ढाँचा_field *field =
			e->ढाँचा_desc->fields[i];

		अगर (is_ima_ढाँचा && म_भेद(field->field_id, "d") == 0)
			show = IMA_SHOW_BINARY_NO_FIELD_LEN;
		अगर (is_ima_ढाँचा && म_भेद(field->field_id, "n") == 0)
			show = IMA_SHOW_BINARY_OLD_STRING_FMT;
		field->field_show(m, show, &e->ढाँचा_data[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ima_measurments_seqops = अणु
	.start = ima_measurements_start,
	.next = ima_measurements_next,
	.stop = ima_measurements_stop,
	.show = ima_measurements_show
पूर्ण;

अटल पूर्णांक ima_measurements_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &ima_measurments_seqops);
पूर्ण

अटल स्थिर काष्ठा file_operations ima_measurements_ops = अणु
	.खोलो = ima_measurements_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = seq_release,
पूर्ण;

व्योम ima_prपूर्णांक_digest(काष्ठा seq_file *m, u8 *digest, u32 size)
अणु
	u32 i;

	क्रम (i = 0; i < size; i++)
		seq_म_लिखो(m, "%02x", *(digest + i));
पूर्ण

/* prपूर्णांक in ascii */
अटल पूर्णांक ima_ascii_measurements_show(काष्ठा seq_file *m, व्योम *v)
अणु
	/* the list never shrinks, so we करोn't need a lock here */
	काष्ठा ima_queue_entry *qe = v;
	काष्ठा ima_ढाँचा_entry *e;
	अक्षर *ढाँचा_name;
	पूर्णांक i;

	/* get entry */
	e = qe->entry;
	अगर (e == शून्य)
		वापस -1;

	ढाँचा_name = (e->ढाँचा_desc->name[0] != '\0') ?
	    e->ढाँचा_desc->name : e->ढाँचा_desc->fmt;

	/* 1st: PCR used (config option) */
	seq_म_लिखो(m, "%2d ", e->pcr);

	/* 2nd: SHA1 ढाँचा hash */
	ima_prपूर्णांक_digest(m, e->digests[ima_sha1_idx].digest, TPM_DIGEST_SIZE);

	/* 3th:  ढाँचा name */
	seq_म_लिखो(m, " %s", ढाँचा_name);

	/* 4th:  ढाँचा specअगरic data */
	क्रम (i = 0; i < e->ढाँचा_desc->num_fields; i++) अणु
		seq_माला_दो(m, " ");
		अगर (e->ढाँचा_data[i].len == 0)
			जारी;

		e->ढाँचा_desc->fields[i]->field_show(m, IMA_SHOW_ASCII,
							&e->ढाँचा_data[i]);
	पूर्ण
	seq_माला_दो(m, "\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ima_ascii_measurements_seqops = अणु
	.start = ima_measurements_start,
	.next = ima_measurements_next,
	.stop = ima_measurements_stop,
	.show = ima_ascii_measurements_show
पूर्ण;

अटल पूर्णांक ima_ascii_measurements_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &ima_ascii_measurements_seqops);
पूर्ण

अटल स्थिर काष्ठा file_operations ima_ascii_measurements_ops = अणु
	.खोलो = ima_ascii_measurements_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = seq_release,
पूर्ण;

अटल sमाप_प्रकार ima_पढ़ो_policy(अक्षर *path)
अणु
	व्योम *data = शून्य;
	अक्षर *datap;
	माप_प्रकार size;
	पूर्णांक rc, pathlen = म_माप(path);

	अक्षर *p;

	/* हटाओ \न */
	datap = path;
	strsep(&datap, "\n");

	rc = kernel_पढ़ो_file_from_path(path, 0, &data, पूर्णांक_उच्च, शून्य,
					READING_POLICY);
	अगर (rc < 0) अणु
		pr_err("Unable to open file: %s (%d)", path, rc);
		वापस rc;
	पूर्ण
	size = rc;
	rc = 0;

	datap = data;
	जबतक (size > 0 && (p = strsep(&datap, "\n"))) अणु
		pr_debug("rule: %s\n", p);
		rc = ima_parse_add_rule(p);
		अगर (rc < 0)
			अवरोध;
		size -= rc;
	पूर्ण

	vमुक्त(data);
	अगर (rc < 0)
		वापस rc;
	अन्यथा अगर (size)
		वापस -EINVAL;
	अन्यथा
		वापस pathlen;
पूर्ण

अटल sमाप_प्रकार ima_ग_लिखो_policy(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार datalen, loff_t *ppos)
अणु
	अक्षर *data;
	sमाप_प्रकार result;

	अगर (datalen >= PAGE_SIZE)
		datalen = PAGE_SIZE - 1;

	/* No partial ग_लिखोs. */
	result = -EINVAL;
	अगर (*ppos != 0)
		जाओ out;

	data = memdup_user_nul(buf, datalen);
	अगर (IS_ERR(data)) अणु
		result = PTR_ERR(data);
		जाओ out;
	पूर्ण

	result = mutex_lock_पूर्णांकerruptible(&ima_ग_लिखो_mutex);
	अगर (result < 0)
		जाओ out_मुक्त;

	अगर (data[0] == '/') अणु
		result = ima_पढ़ो_policy(data);
	पूर्ण अन्यथा अगर (ima_appउठाओ & IMA_APPRAISE_POLICY) अणु
		pr_err("signed policy file (specified as an absolute pathname) required\n");
		पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_STATUS, शून्य, शून्य,
				    "policy_update", "signed policy required",
				    1, 0);
		result = -EACCES;
	पूर्ण अन्यथा अणु
		result = ima_parse_add_rule(data);
	पूर्ण
	mutex_unlock(&ima_ग_लिखो_mutex);
out_मुक्त:
	kमुक्त(data);
out:
	अगर (result < 0)
		valid_policy = 0;

	वापस result;
पूर्ण

अटल काष्ठा dentry *ima_dir;
अटल काष्ठा dentry *ima_symlink;
अटल काष्ठा dentry *binary_runसमय_measurements;
अटल काष्ठा dentry *ascii_runसमय_measurements;
अटल काष्ठा dentry *runसमय_measurements_count;
अटल काष्ठा dentry *violations;
अटल काष्ठा dentry *ima_policy;

क्रमागत ima_fs_flags अणु
	IMA_FS_BUSY,
पूर्ण;

अटल अचिन्हित दीर्घ ima_fs_flags;

#अगर_घोषित	CONFIG_IMA_READ_POLICY
अटल स्थिर काष्ठा seq_operations ima_policy_seqops = अणु
		.start = ima_policy_start,
		.next = ima_policy_next,
		.stop = ima_policy_stop,
		.show = ima_policy_show,
पूर्ण;
#पूर्ण_अगर

/*
 * ima_खोलो_policy: sequentialize access to the policy file
 */
अटल पूर्णांक ima_खोलो_policy(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अगर (!(filp->f_flags & O_WRONLY)) अणु
#अगर_अघोषित	CONFIG_IMA_READ_POLICY
		वापस -EACCES;
#अन्यथा
		अगर ((filp->f_flags & O_ACCMODE) != O_RDONLY)
			वापस -EACCES;
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		वापस seq_खोलो(filp, &ima_policy_seqops);
#पूर्ण_अगर
	पूर्ण
	अगर (test_and_set_bit(IMA_FS_BUSY, &ima_fs_flags))
		वापस -EBUSY;
	वापस 0;
पूर्ण

/*
 * ima_release_policy - start using the new measure policy rules.
 *
 * Initially, ima_measure poपूर्णांकs to the शेष policy rules, now
 * poपूर्णांक to the new policy rules, and हटाओ the securityfs policy file,
 * assuming a valid policy.
 */
अटल पूर्णांक ima_release_policy(काष्ठा inode *inode, काष्ठा file *file)
अणु
	स्थिर अक्षर *cause = valid_policy ? "completed" : "failed";

	अगर ((file->f_flags & O_ACCMODE) == O_RDONLY)
		वापस seq_release(inode, file);

	अगर (valid_policy && ima_check_policy() < 0) अणु
		cause = "failed";
		valid_policy = 0;
	पूर्ण

	pr_info("policy update %s\n", cause);
	पूर्णांकegrity_audit_msg(AUDIT_INTEGRITY_STATUS, शून्य, शून्य,
			    "policy_update", cause, !valid_policy, 0);

	अगर (!valid_policy) अणु
		ima_delete_rules();
		valid_policy = 1;
		clear_bit(IMA_FS_BUSY, &ima_fs_flags);
		वापस 0;
	पूर्ण

	ima_update_policy();
#अगर !defined(CONFIG_IMA_WRITE_POLICY) && !defined(CONFIG_IMA_READ_POLICY)
	securityfs_हटाओ(ima_policy);
	ima_policy = शून्य;
#या_अगर defined(CONFIG_IMA_WRITE_POLICY)
	clear_bit(IMA_FS_BUSY, &ima_fs_flags);
#या_अगर defined(CONFIG_IMA_READ_POLICY)
	inode->i_mode &= ~S_IWUSR;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations ima_measure_policy_ops = अणु
	.खोलो = ima_खोलो_policy,
	.ग_लिखो = ima_ग_लिखो_policy,
	.पढ़ो = seq_पढ़ो,
	.release = ima_release_policy,
	.llseek = generic_file_llseek,
पूर्ण;

पूर्णांक __init ima_fs_init(व्योम)
अणु
	ima_dir = securityfs_create_dir("ima", पूर्णांकegrity_dir);
	अगर (IS_ERR(ima_dir))
		वापस -1;

	ima_symlink = securityfs_create_symlink("ima", शून्य, "integrity/ima",
						शून्य);
	अगर (IS_ERR(ima_symlink))
		जाओ out;

	binary_runसमय_measurements =
	    securityfs_create_file("binary_runtime_measurements",
				   S_IRUSR | S_IRGRP, ima_dir, शून्य,
				   &ima_measurements_ops);
	अगर (IS_ERR(binary_runसमय_measurements))
		जाओ out;

	ascii_runसमय_measurements =
	    securityfs_create_file("ascii_runtime_measurements",
				   S_IRUSR | S_IRGRP, ima_dir, शून्य,
				   &ima_ascii_measurements_ops);
	अगर (IS_ERR(ascii_runसमय_measurements))
		जाओ out;

	runसमय_measurements_count =
	    securityfs_create_file("runtime_measurements_count",
				   S_IRUSR | S_IRGRP, ima_dir, शून्य,
				   &ima_measurements_count_ops);
	अगर (IS_ERR(runसमय_measurements_count))
		जाओ out;

	violations =
	    securityfs_create_file("violations", S_IRUSR | S_IRGRP,
				   ima_dir, शून्य, &ima_htable_violations_ops);
	अगर (IS_ERR(violations))
		जाओ out;

	ima_policy = securityfs_create_file("policy", POLICY_खाता_FLAGS,
					    ima_dir, शून्य,
					    &ima_measure_policy_ops);
	अगर (IS_ERR(ima_policy))
		जाओ out;

	वापस 0;
out:
	securityfs_हटाओ(violations);
	securityfs_हटाओ(runसमय_measurements_count);
	securityfs_हटाओ(ascii_runसमय_measurements);
	securityfs_हटाओ(binary_runसमय_measurements);
	securityfs_हटाओ(ima_symlink);
	securityfs_हटाओ(ima_dir);
	securityfs_हटाओ(ima_policy);
	वापस -1;
पूर्ण
