<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    HMC Drive FTP Services
 *
 *    Copyright IBM Corp. 2013
 *    Author(s): Ralf Hoppe (rhoppe@de.ibm.com)
 */

#घोषणा KMSG_COMPONENT "hmcdrv"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/export.h>

#समावेश <linux/प्रकार.स>
#समावेश <linux/crc16.h>

#समावेश "hmcdrv_ftp.h"
#समावेश "hmcdrv_cache.h"
#समावेश "sclp_ftp.h"
#समावेश "diag_ftp.h"

/**
 * काष्ठा hmcdrv_ftp_ops - HMC drive FTP operations
 * @startup: startup function
 * @shutकरोwn: shutकरोwn function
 * @cmd: FTP transfer function
 */
काष्ठा hmcdrv_ftp_ops अणु
	पूर्णांक (*startup)(व्योम);
	व्योम (*shutकरोwn)(व्योम);
	sमाप_प्रकार (*transfer)(स्थिर काष्ठा hmcdrv_ftp_cmdspec *ftp,
			    माप_प्रकार *fsize);
पूर्ण;

अटल क्रमागत hmcdrv_ftp_cmdid hmcdrv_ftp_cmd_getid(स्थिर अक्षर *cmd, पूर्णांक len);
अटल पूर्णांक hmcdrv_ftp_parse(अक्षर *cmd, काष्ठा hmcdrv_ftp_cmdspec *ftp);

अटल स्थिर काष्ठा hmcdrv_ftp_ops *hmcdrv_ftp_funcs; /* current operations */
अटल DEFINE_MUTEX(hmcdrv_ftp_mutex); /* mutex क्रम hmcdrv_ftp_funcs */
अटल अचिन्हित hmcdrv_ftp_refcnt; /* start/shutकरोwn reference counter */

/**
 * hmcdrv_ftp_cmd_getid() - determine FTP command ID from a command string
 * @cmd: FTP command string (NOT zero-terminated)
 * @len: length of FTP command string in @cmd
 */
अटल क्रमागत hmcdrv_ftp_cmdid hmcdrv_ftp_cmd_getid(स्थिर अक्षर *cmd, पूर्णांक len)
अणु
	/* HMC FTP command descriptor */
	काष्ठा hmcdrv_ftp_cmd_desc अणु
		स्थिर अक्षर *str;	   /* command string */
		क्रमागत hmcdrv_ftp_cmdid cmd; /* associated command as क्रमागत */
	पूर्ण;

	/* Description of all HMC drive FTP commands
	 *
	 * Notes:
	 * 1. Array size should be a prime number.
	 * 2. Do not change the order of commands in table (because the
	 *    index is determined by CRC % ARRAY_SIZE).
	 * 3. Original command 'nlist' was नामd, अन्यथा the CRC would
	 *    collide with 'append' (see poपूर्णांक 2).
	 */
	अटल स्थिर काष्ठा hmcdrv_ftp_cmd_desc ftpcmds[7] = अणु

		अणु.str = "get", /* [0] get (CRC = 0x68eb) */
		 .cmd = HMCDRV_FTP_GETपूर्ण,
		अणु.str = "dir", /* [1] dir (CRC = 0x6a9e) */
		 .cmd = HMCDRV_FTP_सूचीपूर्ण,
		अणु.str = "delete", /* [2] delete (CRC = 0x53ae) */
		 .cmd = HMCDRV_FTP_DELETEपूर्ण,
		अणु.str = "nls", /* [3] nls (CRC = 0xf87c) */
		 .cmd = HMCDRV_FTP_NLISTपूर्ण,
		अणु.str = "put", /* [4] put (CRC = 0xac56) */
		 .cmd = HMCDRV_FTP_PUTपूर्ण,
		अणु.str = "append", /* [5] append (CRC = 0xf56e) */
		 .cmd = HMCDRV_FTP_APPENDपूर्ण,
		अणु.str = शून्यपूर्ण /* [6] unused */
	पूर्ण;

	स्थिर काष्ठा hmcdrv_ftp_cmd_desc *pdesc;

	u16 crc = 0xffffU;

	अगर (len == 0)
		वापस HMCDRV_FTP_NOOP; /* error indiactor */

	crc = crc16(crc, cmd, len);
	pdesc = ftpcmds + (crc % ARRAY_SIZE(ftpcmds));
	pr_debug("FTP command '%s' has CRC 0x%04x, at table pos. %lu\n",
		 cmd, crc, (crc % ARRAY_SIZE(ftpcmds)));

	अगर (!pdesc->str || म_भेदन(pdesc->str, cmd, len))
		वापस HMCDRV_FTP_NOOP;

	pr_debug("FTP command '%s' found, with ID %d\n",
		 pdesc->str, pdesc->cmd);

	वापस pdesc->cmd;
पूर्ण

/**
 * hmcdrv_ftp_parse() - HMC drive FTP command parser
 * @cmd: FTP command string "<cmd> <filename>"
 * @ftp: Poपूर्णांकer to FTP command specअगरication buffer (output)
 *
 * Return: 0 on success, अन्यथा a (negative) error code
 */
अटल पूर्णांक hmcdrv_ftp_parse(अक्षर *cmd, काष्ठा hmcdrv_ftp_cmdspec *ftp)
अणु
	अक्षर *start;
	पूर्णांक argc = 0;

	ftp->id = HMCDRV_FTP_NOOP;
	ftp->fname = शून्य;

	जबतक (*cmd != '\0') अणु

		जबतक (है_खाली(*cmd))
			++cmd;

		अगर (*cmd == '\0')
			अवरोध;

		start = cmd;

		चयन (argc) अणु
		हाल 0: /* 1st argument (FTP command) */
			जबतक ((*cmd != '\0') && !है_खाली(*cmd))
				++cmd;
			ftp->id = hmcdrv_ftp_cmd_getid(start, cmd - start);
			अवरोध;
		हाल 1: /* 2nd / last argument (rest of line) */
			जबतक ((*cmd != '\0') && !है_नियंत्रण(*cmd))
				++cmd;
			ftp->fname = start;
			fallthrough;
		शेष:
			*cmd = '\0';
			अवरोध;
		पूर्ण /* चयन */

		++argc;
	पूर्ण /* जबतक */

	अगर (!ftp->fname || (ftp->id == HMCDRV_FTP_NOOP))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * hmcdrv_ftp_करो() - perक्रमm a HMC drive FTP, with data from kernel-space
 * @ftp: poपूर्णांकer to FTP command specअगरication
 *
 * Return: number of bytes पढ़ो/written or a negative error code
 */
sमाप_प्रकार hmcdrv_ftp_करो(स्थिर काष्ठा hmcdrv_ftp_cmdspec *ftp)
अणु
	sमाप_प्रकार len;

	mutex_lock(&hmcdrv_ftp_mutex);

	अगर (hmcdrv_ftp_funcs && hmcdrv_ftp_refcnt) अणु
		pr_debug("starting transfer, cmd %d for '%s' at %lld with %zd bytes\n",
			 ftp->id, ftp->fname, (दीर्घ दीर्घ) ftp->ofs, ftp->len);
		len = hmcdrv_cache_cmd(ftp, hmcdrv_ftp_funcs->transfer);
	पूर्ण अन्यथा अणु
		len = -ENXIO;
	पूर्ण

	mutex_unlock(&hmcdrv_ftp_mutex);
	वापस len;
पूर्ण
EXPORT_SYMBOL(hmcdrv_ftp_करो);

/**
 * hmcdrv_ftp_probe() - probe क्रम the HMC drive FTP service
 *
 * Return: 0 अगर service is available, अन्यथा an (negative) error code
 */
पूर्णांक hmcdrv_ftp_probe(व्योम)
अणु
	पूर्णांक rc;

	काष्ठा hmcdrv_ftp_cmdspec ftp = अणु
		.id = HMCDRV_FTP_NOOP,
		.ofs = 0,
		.fname = "",
		.len = PAGE_SIZE
	पूर्ण;

	ftp.buf = (व्योम *) get_zeroed_page(GFP_KERNEL | GFP_DMA);

	अगर (!ftp.buf)
		वापस -ENOMEM;

	rc = hmcdrv_ftp_startup();

	अगर (rc)
		जाओ out;

	rc = hmcdrv_ftp_करो(&ftp);
	hmcdrv_ftp_shutकरोwn();

	चयन (rc) अणु
	हाल -ENOENT: /* no such file/media or currently busy, */
	हाल -EBUSY:  /* but service seems to be available */
		rc = 0;
		अवरोध;
	शेष: /* leave 'rc' as it is क्रम [0, -EPERM, -E...] */
		अगर (rc > 0)
			rc = 0; /* clear length (success) */
		अवरोध;
	पूर्ण /* चयन */
out:
	मुक्त_page((अचिन्हित दीर्घ) ftp.buf);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(hmcdrv_ftp_probe);

/**
 * hmcdrv_ftp_cmd() - Perक्रमm a HMC drive FTP, with data from user-space
 *
 * @cmd: FTP command string "<cmd> <filename>"
 * @offset: file position to पढ़ो/ग_लिखो
 * @buf: user-space buffer क्रम पढ़ो/written directory/file
 * @len: size of @buf (पढ़ो/dir) or number of bytes to ग_लिखो
 *
 * This function must not be called beक्रमe hmcdrv_ftp_startup() was called.
 *
 * Return: number of bytes पढ़ो/written or a negative error code
 */
sमाप_प्रकार hmcdrv_ftp_cmd(अक्षर __kernel *cmd, loff_t offset,
		       अक्षर __user *buf, माप_प्रकार len)
अणु
	पूर्णांक order;

	काष्ठा hmcdrv_ftp_cmdspec ftp = अणु.len = len, .ofs = offsetपूर्ण;
	sमाप_प्रकार retlen = hmcdrv_ftp_parse(cmd, &ftp);

	अगर (retlen)
		वापस retlen;

	order = get_order(ftp.len);
	ftp.buf = (व्योम *) __get_मुक्त_pages(GFP_KERNEL | GFP_DMA, order);

	अगर (!ftp.buf)
		वापस -ENOMEM;

	चयन (ftp.id) अणु
	हाल HMCDRV_FTP_सूची:
	हाल HMCDRV_FTP_NLIST:
	हाल HMCDRV_FTP_GET:
		retlen = hmcdrv_ftp_करो(&ftp);

		अगर ((retlen >= 0) &&
		    copy_to_user(buf, ftp.buf, retlen))
			retlen = -EFAULT;
		अवरोध;

	हाल HMCDRV_FTP_PUT:
	हाल HMCDRV_FTP_APPEND:
		अगर (!copy_from_user(ftp.buf, buf, ftp.len))
			retlen = hmcdrv_ftp_करो(&ftp);
		अन्यथा
			retlen = -EFAULT;
		अवरोध;

	हाल HMCDRV_FTP_DELETE:
		retlen = hmcdrv_ftp_करो(&ftp);
		अवरोध;

	शेष:
		retlen = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	मुक्त_pages((अचिन्हित दीर्घ) ftp.buf, order);
	वापस retlen;
पूर्ण

/**
 * hmcdrv_ftp_startup() - startup of HMC drive FTP functionality क्रम a
 * dedicated (owner) instance
 *
 * Return: 0 on success, अन्यथा an (negative) error code
 */
पूर्णांक hmcdrv_ftp_startup(व्योम)
अणु
	अटल स्थिर काष्ठा hmcdrv_ftp_ops hmcdrv_ftp_zvm = अणु
		.startup = diag_ftp_startup,
		.shutकरोwn = diag_ftp_shutकरोwn,
		.transfer = diag_ftp_cmd
	पूर्ण;

	अटल स्थिर काष्ठा hmcdrv_ftp_ops hmcdrv_ftp_lpar = अणु
		.startup = sclp_ftp_startup,
		.shutकरोwn = sclp_ftp_shutकरोwn,
		.transfer = sclp_ftp_cmd
	पूर्ण;

	पूर्णांक rc = 0;

	mutex_lock(&hmcdrv_ftp_mutex); /* block transfers जबतक start-up */

	अगर (hmcdrv_ftp_refcnt == 0) अणु
		अगर (MACHINE_IS_VM)
			hmcdrv_ftp_funcs = &hmcdrv_ftp_zvm;
		अन्यथा अगर (MACHINE_IS_LPAR || MACHINE_IS_KVM)
			hmcdrv_ftp_funcs = &hmcdrv_ftp_lpar;
		अन्यथा
			rc = -EOPNOTSUPP;

		अगर (hmcdrv_ftp_funcs)
			rc = hmcdrv_ftp_funcs->startup();
	पूर्ण

	अगर (!rc)
		++hmcdrv_ftp_refcnt;

	mutex_unlock(&hmcdrv_ftp_mutex);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(hmcdrv_ftp_startup);

/**
 * hmcdrv_ftp_shutकरोwn() - shutकरोwn of HMC drive FTP functionality क्रम a
 * dedicated (owner) instance
 */
व्योम hmcdrv_ftp_shutकरोwn(व्योम)
अणु
	mutex_lock(&hmcdrv_ftp_mutex);
	--hmcdrv_ftp_refcnt;

	अगर ((hmcdrv_ftp_refcnt == 0) && hmcdrv_ftp_funcs)
		hmcdrv_ftp_funcs->shutकरोwn();

	mutex_unlock(&hmcdrv_ftp_mutex);
पूर्ण
EXPORT_SYMBOL(hmcdrv_ftp_shutकरोwn);
