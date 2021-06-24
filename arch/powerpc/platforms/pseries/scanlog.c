<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  c 2001 PPC 64 Team, IBM Corp
 *
 * scan-log-data driver क्रम PPC64  Todd Inglett <tinglett@vnet.ibm.com>
 *
 * When ppc64 hardware fails the service processor dumps पूर्णांकernal state
 * of the प्रणाली.  After a reboot the operating प्रणाली can access a dump
 * of this data using this driver.  A dump exists अगर the device-tree
 * /chosen/ibm,scan-log-data property exists.
 *
 * This driver exports /proc/घातerpc/scan-log-dump which can be पढ़ो.
 * The driver supports only sequential पढ़ोs.
 *
 * The driver looks at a ग_लिखो to the driver क्रम the single word "reset".
 * If given, the driver will reset the scanlog so the platक्रमm can मुक्त it.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/prom.h>

#घोषणा MODULE_VERS "1.0"
#घोषणा MODULE_NAME "scanlog"

/* Status वापसs from ibm,scan-log-dump */
#घोषणा SCANLOG_COMPLETE 0
#घोषणा SCANLOG_HWERROR -1
#घोषणा SCANLOG_CONTINUE 1


अटल अचिन्हित पूर्णांक ibm_scan_log_dump;			/* RTAS token */
अटल अचिन्हित पूर्णांक *scanlog_buffer;			/* The data buffer */

अटल sमाप_प्रकार scanlog_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक *data = scanlog_buffer;
	पूर्णांक status;
	अचिन्हित दीर्घ len, off;
	अचिन्हित पूर्णांक रुको_समय;

	अगर (count > RTAS_DATA_BUF_SIZE)
		count = RTAS_DATA_BUF_SIZE;

	अगर (count < 1024) अणु
		/* This is the min supported by this RTAS call.  Rather
		 * than करो all the buffering we insist the user code handle
		 * larger पढ़ोs.  As दीर्घ as cp works... :)
		 */
		prपूर्णांकk(KERN_ERR "scanlog: cannot perform a small read (%ld)\n", count);
		वापस -EINVAL;
	पूर्ण

	अगर (!access_ok(buf, count))
		वापस -EFAULT;

	क्रम (;;) अणु
		रुको_समय = 500;	/* शेष रुको अगर no data */
		spin_lock(&rtas_data_buf_lock);
		स_नकल(rtas_data_buf, data, RTAS_DATA_BUF_SIZE);
		status = rtas_call(ibm_scan_log_dump, 2, 1, शून्य,
				   (u32) __pa(rtas_data_buf), (u32) count);
		स_नकल(data, rtas_data_buf, RTAS_DATA_BUF_SIZE);
		spin_unlock(&rtas_data_buf_lock);

		pr_debug("scanlog: status=%d, data[0]=%x, data[1]=%x, " \
			 "data[2]=%x\n", status, data[0], data[1], data[2]);
		चयन (status) अणु
		    हाल SCANLOG_COMPLETE:
			pr_debug("scanlog: hit eof\n");
			वापस 0;
		    हाल SCANLOG_HWERROR:
			pr_debug("scanlog: hardware error reading data\n");
			वापस -EIO;
		    हाल SCANLOG_CONTINUE:
			/* We may or may not have data yet */
			len = data[1];
			off = data[2];
			अगर (len > 0) अणु
				अगर (copy_to_user(buf, ((अक्षर *)data)+off, len))
					वापस -EFAULT;
				वापस len;
			पूर्ण
			/* Break to sleep शेष समय */
			अवरोध;
		    शेष:
			/* Assume extended busy */
			रुको_समय = rtas_busy_delay_समय(status);
			अगर (!रुको_समय) अणु
				prपूर्णांकk(KERN_ERR "scanlog: unknown error " \
				       "from rtas: %d\n", status);
				वापस -EIO;
			पूर्ण
		पूर्ण
		/* Apparently no data yet.  Wait and try again. */
		msleep_पूर्णांकerruptible(रुको_समय);
	पूर्ण
	/*NOTREACHED*/
पूर्ण

अटल sमाप_प्रकार scanlog_ग_लिखो(काष्ठा file * file, स्थिर अक्षर __user * buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर stkbuf[20];
	पूर्णांक status;

	अगर (count > 19) count = 19;
	अगर (copy_from_user (stkbuf, buf, count)) अणु
		वापस -EFAULT;
	पूर्ण
	stkbuf[count] = 0;

	अगर (buf) अणु
		अगर (म_भेदन(stkbuf, "reset", 5) == 0) अणु
			pr_debug("scanlog: reset scanlog\n");
			status = rtas_call(ibm_scan_log_dump, 2, 1, शून्य, 0, 0);
			pr_debug("scanlog: rtas returns %d\n", status);
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक scanlog_खोलो(काष्ठा inode * inode, काष्ठा file * file)
अणु
	अचिन्हित पूर्णांक *data = scanlog_buffer;

	अगर (data[0] != 0) अणु
		/* This imperfect test stops a second copy of the
		 * data (or a reset जबतक data is being copied)
		 */
		वापस -EBUSY;
	पूर्ण

	data[0] = 0;	/* re-init so we restart the scan */

	वापस 0;
पूर्ण

अटल पूर्णांक scanlog_release(काष्ठा inode * inode, काष्ठा file * file)
अणु
	अचिन्हित पूर्णांक *data = scanlog_buffer;

	data[0] = 0;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा proc_ops scanlog_proc_ops = अणु
	.proc_पढ़ो	= scanlog_पढ़ो,
	.proc_ग_लिखो	= scanlog_ग_लिखो,
	.proc_खोलो	= scanlog_खोलो,
	.proc_release	= scanlog_release,
	.proc_lseek	= noop_llseek,
पूर्ण;

अटल पूर्णांक __init scanlog_init(व्योम)
अणु
	काष्ठा proc_dir_entry *ent;
	पूर्णांक err = -ENOMEM;

	ibm_scan_log_dump = rtas_token("ibm,scan-log-dump");
	अगर (ibm_scan_log_dump == RTAS_UNKNOWN_SERVICE)
		वापस -ENODEV;

	/* Ideally we could allocate a buffer < 4G */
	scanlog_buffer = kzalloc(RTAS_DATA_BUF_SIZE, GFP_KERNEL);
	अगर (!scanlog_buffer)
		जाओ err;

	ent = proc_create("powerpc/rtas/scan-log-dump", 0400, शून्य,
			  &scanlog_proc_ops);
	अगर (!ent)
		जाओ err;
	वापस 0;
err:
	kमुक्त(scanlog_buffer);
	वापस err;
पूर्ण

अटल व्योम __निकास scanlog_cleanup(व्योम)
अणु
	हटाओ_proc_entry("powerpc/rtas/scan-log-dump", शून्य);
	kमुक्त(scanlog_buffer);
पूर्ण

module_init(scanlog_init);
module_निकास(scanlog_cleanup);
MODULE_LICENSE("GPL");
