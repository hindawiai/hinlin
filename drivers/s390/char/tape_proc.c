<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    tape device driver क्रम S/390 and zSeries tapes.
 *
 *  S390 and zSeries version
 *    Copyright IBM Corp. 2001
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 *		 Michael Holzheu <holzheu@de.ibm.com>
 *		 Tuan Ngo-Anh <ngoanh@de.ibm.com>
 *
 * PROCFS Functions
 */

#घोषणा KMSG_COMPONENT "tape"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/proc_fs.h>

#घोषणा TAPE_DBF_AREA	tape_core_dbf

#समावेश "tape.h"

अटल स्थिर अक्षर *tape_med_st_verbose[MS_SIZE] =
अणु
	[MS_UNKNOWN] = "UNKNOWN ",
	[MS_LOADED] = "LOADED  ",
	[MS_UNLOADED] = "UNLOADED"
पूर्ण;

/* our proc tapedevices entry */
अटल काष्ठा proc_dir_entry *tape_proc_devices;

/*
 * Show function क्रम /proc/tapedevices
 */
अटल पूर्णांक tape_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा tape_device *device;
	काष्ठा tape_request *request;
	स्थिर अक्षर *str;
	अचिन्हित दीर्घ n;

	n = (अचिन्हित दीर्घ) v - 1;
	अगर (!n) अणु
		seq_म_लिखो(m, "TapeNo\tBusID      CuType/Model\t"
			"DevType/Model\tBlkSize\tState\tOp\tMedState\n");
	पूर्ण
	device = tape_find_device(n);
	अगर (IS_ERR(device))
		वापस 0;
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	seq_म_लिखो(m, "%d\t", (पूर्णांक) n);
	seq_म_लिखो(m, "%-10.10s ", dev_name(&device->cdev->dev));
	seq_म_लिखो(m, "%04X/", device->cdev->id.cu_type);
	seq_म_लिखो(m, "%02X\t", device->cdev->id.cu_model);
	seq_म_लिखो(m, "%04X/", device->cdev->id.dev_type);
	seq_म_लिखो(m, "%02X\t\t", device->cdev->id.dev_model);
	अगर (device->अक्षर_data.block_size == 0)
		seq_म_लिखो(m, "auto\t");
	अन्यथा
		seq_म_लिखो(m, "%i\t", device->अक्षर_data.block_size);
	अगर (device->tape_state >= 0 &&
	    device->tape_state < TS_SIZE)
		str = tape_state_verbose[device->tape_state];
	अन्यथा
		str = "UNKNOWN";
	seq_म_लिखो(m, "%s\t", str);
	अगर (!list_empty(&device->req_queue)) अणु
		request = list_entry(device->req_queue.next,
				     काष्ठा tape_request, list);
		str = tape_op_verbose[request->op];
	पूर्ण अन्यथा
		str = "---";
	seq_म_लिखो(m, "%s\t", str);
	seq_म_लिखो(m, "%s\n", tape_med_st_verbose[device->medium_state]);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	tape_put_device(device);
        वापस 0;
पूर्ण

अटल व्योम *tape_proc_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	अगर (*pos >= 256 / TAPE_MINORS_PER_DEV)
		वापस शून्य;
	वापस (व्योम *)((अचिन्हित दीर्घ) *pos + 1);
पूर्ण

अटल व्योम *tape_proc_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस tape_proc_start(m, pos);
पूर्ण

अटल व्योम tape_proc_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations tape_proc_seq = अणु
	.start		= tape_proc_start,
	.next		= tape_proc_next,
	.stop		= tape_proc_stop,
	.show		= tape_proc_show,
पूर्ण;

/*
 * Initialize procfs stuff on startup
 */
व्योम
tape_proc_init(व्योम)
अणु
	tape_proc_devices = proc_create_seq("tapedevices", 0444, शून्य,
					    &tape_proc_seq);
पूर्ण

/*
 * Cleanup all stuff रेजिस्टरed to the procfs
 */
व्योम
tape_proc_cleanup(व्योम)
अणु
	अगर (tape_proc_devices != शून्य)
		हटाओ_proc_entry ("tapedevices", शून्य);
पूर्ण
