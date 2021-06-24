<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Sysctl पूर्णांकerface क्रम parport devices.
 * 
 * Authors: David Campbell
 *          Tim Waugh <tim@cyberelk.demon.co.uk>
 *          Philip Blundell <philb@gnu.org>
 *          Andrea Arcangeli
 *          Riccarकरो Facchetti <fizban@tin.it>
 *
 * based on work by Grant Guenther <grant@torque.net>
 *              and Philip Blundell
 *
 * Cleaned up include files - Russell King <linux@arm.uk.linux.org>
 */

#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/parport.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/sysctl.h>
#समावेश <linux/device.h>

#समावेश <linux/uaccess.h>

#अगर defined(CONFIG_SYSCTL) && defined(CONFIG_PROC_FS)

#घोषणा PARPORT_MIN_TIMESLICE_VALUE 1ul 
#घोषणा PARPORT_MAX_TIMESLICE_VALUE ((अचिन्हित दीर्घ) HZ)
#घोषणा PARPORT_MIN_SPINTIME_VALUE 1
#घोषणा PARPORT_MAX_SPINTIME_VALUE 1000

अटल पूर्णांक करो_active_device(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		      व्योम *result, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा parport *port = (काष्ठा parport *)table->extra1;
	अक्षर buffer[256];
	काष्ठा pardevice *dev;
	पूर्णांक len = 0;

	अगर (ग_लिखो)		/* can't happen anyway */
		वापस -EACCES;

	अगर (*ppos) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण
	
	क्रम (dev = port->devices; dev ; dev = dev->next) अणु
		अगर(dev == port->cad) अणु
			len += प्र_लिखो(buffer, "%s\n", dev->name);
		पूर्ण
	पूर्ण

	अगर(!len) अणु
		len += प्र_लिखो(buffer, "%s\n", "none");
	पूर्ण

	अगर (len > *lenp)
		len = *lenp;
	अन्यथा
		*lenp = len;

	*ppos += len;
	स_नकल(result, buffer, len);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PARPORT_1284
अटल पूर्णांक करो_स्वतःprobe(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			व्योम *result, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा parport_device_info *info = table->extra2;
	स्थिर अक्षर *str;
	अक्षर buffer[256];
	पूर्णांक len = 0;

	अगर (ग_लिखो) /* permissions stop this */
		वापस -EACCES;

	अगर (*ppos) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण
	
	अगर ((str = info->class_name) != शून्य)
		len += प्र_लिखो (buffer + len, "CLASS:%s;\n", str);

	अगर ((str = info->model) != शून्य)
		len += प्र_लिखो (buffer + len, "MODEL:%s;\n", str);

	अगर ((str = info->mfr) != शून्य)
		len += प्र_लिखो (buffer + len, "MANUFACTURER:%s;\n", str);

	अगर ((str = info->description) != शून्य)
		len += प्र_लिखो (buffer + len, "DESCRIPTION:%s;\n", str);

	अगर ((str = info->cmdset) != शून्य)
		len += प्र_लिखो (buffer + len, "COMMAND SET:%s;\n", str);

	अगर (len > *lenp)
		len = *lenp;
	अन्यथा
		*lenp = len;

	*ppos += len;

	स_नकल(result, buffer, len);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* IEEE1284.3 support. */

अटल पूर्णांक करो_hardware_base_addr(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				 व्योम *result, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा parport *port = (काष्ठा parport *)table->extra1;
	अक्षर buffer[20];
	पूर्णांक len = 0;

	अगर (*ppos) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण

	अगर (ग_लिखो) /* permissions prevent this anyway */
		वापस -EACCES;

	len += प्र_लिखो (buffer, "%lu\t%lu\n", port->base, port->base_hi);

	अगर (len > *lenp)
		len = *lenp;
	अन्यथा
		*lenp = len;

	*ppos += len;
	स_नकल(result, buffer, len);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_hardware_irq(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			   व्योम *result, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा parport *port = (काष्ठा parport *)table->extra1;
	अक्षर buffer[20];
	पूर्णांक len = 0;

	अगर (*ppos) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण

	अगर (ग_लिखो) /* permissions prevent this anyway */
		वापस -EACCES;

	len += प्र_लिखो (buffer, "%d\n", port->irq);

	अगर (len > *lenp)
		len = *lenp;
	अन्यथा
		*lenp = len;

	*ppos += len;
	स_नकल(result, buffer, len);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_hardware_dma(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			   व्योम *result, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा parport *port = (काष्ठा parport *)table->extra1;
	अक्षर buffer[20];
	पूर्णांक len = 0;

	अगर (*ppos) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण

	अगर (ग_लिखो) /* permissions prevent this anyway */
		वापस -EACCES;

	len += प्र_लिखो (buffer, "%d\n", port->dma);

	अगर (len > *lenp)
		len = *lenp;
	अन्यथा
		*lenp = len;

	*ppos += len;
	स_नकल(result, buffer, len);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_hardware_modes(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			     व्योम *result, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा parport *port = (काष्ठा parport *)table->extra1;
	अक्षर buffer[40];
	पूर्णांक len = 0;

	अगर (*ppos) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण

	अगर (ग_लिखो) /* permissions prevent this anyway */
		वापस -EACCES;

	अणु
#घोषणा prपूर्णांकmode(x)							\
करो अणु									\
	अगर (port->modes & PARPORT_MODE_##x)				\
		len += प्र_लिखो(buffer + len, "%s%s", f++ ? "," : "", #x); \
पूर्ण जबतक (0)
		पूर्णांक f = 0;
		prपूर्णांकmode(PCSPP);
		prपूर्णांकmode(TRISTATE);
		prपूर्णांकmode(COMPAT);
		prपूर्णांकmode(EPP);
		prपूर्णांकmode(ECP);
		prपूर्णांकmode(DMA);
#अघोषित prपूर्णांकmode
	पूर्ण
	buffer[len++] = '\n';

	अगर (len > *lenp)
		len = *lenp;
	अन्यथा
		*lenp = len;

	*ppos += len;
	स_नकल(result, buffer, len);
	वापस 0;
पूर्ण

#घोषणा PARPORT_PORT_सूची(CHILD) अणु .procname = शून्य, .mode = 0555, .child = CHILD पूर्ण
#घोषणा PARPORT_PARPORT_सूची(CHILD) अणु .procname = "parport", \
                                     .mode = 0555, .child = CHILD पूर्ण
#घोषणा PARPORT_DEV_सूची(CHILD) अणु .procname = "dev", .mode = 0555, .child = CHILD पूर्ण
#घोषणा PARPORT_DEVICES_ROOT_सूची  अणु  .procname = "devices", \
                                    .mode = 0555, .child = शून्य पूर्ण

अटल स्थिर अचिन्हित दीर्घ parport_min_बारlice_value =
PARPORT_MIN_TIMESLICE_VALUE;

अटल स्थिर अचिन्हित दीर्घ parport_max_बारlice_value =
PARPORT_MAX_TIMESLICE_VALUE;

अटल स्थिर  पूर्णांक parport_min_spपूर्णांकime_value =
PARPORT_MIN_SPINTIME_VALUE;

अटल स्थिर पूर्णांक parport_max_spपूर्णांकime_value =
PARPORT_MAX_SPINTIME_VALUE;


काष्ठा parport_sysctl_table अणु
	काष्ठा ctl_table_header *sysctl_header;
	काष्ठा ctl_table vars[12];
	काष्ठा ctl_table device_dir[2];
	काष्ठा ctl_table port_dir[2];
	काष्ठा ctl_table parport_dir[2];
	काष्ठा ctl_table dev_dir[2];
पूर्ण;

अटल स्थिर काष्ठा parport_sysctl_table parport_sysctl_ढाँचा = अणु
	.sysctl_header = शून्य,
        अणु
		अणु
			.procname	= "spintime",
			.data		= शून्य,
			.maxlen		= माप(पूर्णांक),
			.mode		= 0644,
			.proc_handler	= proc_करोपूर्णांकvec_minmax,
			.extra1		= (व्योम*) &parport_min_spपूर्णांकime_value,
			.extra2		= (व्योम*) &parport_max_spपूर्णांकime_value
		पूर्ण,
		अणु
			.procname	= "base-addr",
			.data		= शून्य,
			.maxlen		= 0,
			.mode		= 0444,
			.proc_handler	= करो_hardware_base_addr
		पूर्ण,
		अणु
			.procname	= "irq",
			.data		= शून्य,
			.maxlen		= 0,
			.mode		= 0444,
			.proc_handler	= करो_hardware_irq
		पूर्ण,
		अणु
			.procname	= "dma",
			.data		= शून्य,
			.maxlen		= 0,
			.mode		= 0444,
			.proc_handler	= करो_hardware_dma
		पूर्ण,
		अणु
			.procname	= "modes",
			.data		= शून्य,
			.maxlen		= 0,
			.mode		= 0444,
			.proc_handler	= करो_hardware_modes
		पूर्ण,
		PARPORT_DEVICES_ROOT_सूची,
#अगर_घोषित CONFIG_PARPORT_1284
		अणु
			.procname	= "autoprobe",
			.data		= शून्य,
			.maxlen		= 0,
			.mode		= 0444,
			.proc_handler	= करो_स्वतःprobe
		पूर्ण,
		अणु
			.procname	= "autoprobe0",
			.data		= शून्य,
			.maxlen		= 0,
			.mode		= 0444,
			.proc_handler	= करो_स्वतःprobe
		पूर्ण,
		अणु
			.procname	= "autoprobe1",
			.data		= शून्य,
			.maxlen		= 0,
			.mode		= 0444,
			.proc_handler	= करो_स्वतःprobe
		पूर्ण,
		अणु
			.procname	= "autoprobe2",
			.data		= शून्य,
			.maxlen		= 0,
			.mode		= 0444,
			.proc_handler	= करो_स्वतःprobe
		पूर्ण,
		अणु
			.procname	= "autoprobe3",
			.data		= शून्य,
			.maxlen		= 0,
			.mode		= 0444,
			.proc_handler	= करो_स्वतःprobe
		पूर्ण,
#पूर्ण_अगर /* IEEE 1284 support */
		अणुपूर्ण
	पूर्ण,
	अणु
		अणु
			.procname	= "active",
			.data		= शून्य,
			.maxlen		= 0,
			.mode		= 0444,
			.proc_handler	= करो_active_device
		पूर्ण,
		अणुपूर्ण
	पूर्ण,
	अणु
		PARPORT_PORT_सूची(शून्य),
		अणुपूर्ण
	पूर्ण,
	अणु
		PARPORT_PARPORT_सूची(शून्य),
		अणुपूर्ण
	पूर्ण,
	अणु
		PARPORT_DEV_सूची(शून्य),
		अणुपूर्ण
	पूर्ण
पूर्ण;

काष्ठा parport_device_sysctl_table
अणु
	काष्ठा ctl_table_header *sysctl_header;
	काष्ठा ctl_table vars[2];
	काष्ठा ctl_table device_dir[2];
	काष्ठा ctl_table devices_root_dir[2];
	काष्ठा ctl_table port_dir[2];
	काष्ठा ctl_table parport_dir[2];
	काष्ठा ctl_table dev_dir[2];
पूर्ण;

अटल स्थिर काष्ठा parport_device_sysctl_table
parport_device_sysctl_ढाँचा = अणु
	.sysctl_header = शून्य,
	अणु
		अणु
			.procname 	= "timeslice",
			.data		= शून्य,
			.maxlen		= माप(अचिन्हित दीर्घ),
			.mode		= 0644,
			.proc_handler	= proc_करोuदीर्घvec_ms_jअगरfies_minmax,
			.extra1		= (व्योम*) &parport_min_बारlice_value,
			.extra2		= (व्योम*) &parport_max_बारlice_value
		पूर्ण,
	पूर्ण,
	अणु
		अणु
			.procname	= शून्य,
			.data		= शून्य,
			.maxlen		= 0,
			.mode		= 0555,
			.child		= शून्य
		पूर्ण,
		अणुपूर्ण
	पूर्ण,
	अणु
		PARPORT_DEVICES_ROOT_सूची,
		अणुपूर्ण
	पूर्ण,
	अणु
		PARPORT_PORT_सूची(शून्य),
		अणुपूर्ण
	पूर्ण,
	अणु
		PARPORT_PARPORT_सूची(शून्य),
		अणुपूर्ण
	पूर्ण,
	अणु
		PARPORT_DEV_सूची(शून्य),
		अणुपूर्ण
	पूर्ण
पूर्ण;

काष्ठा parport_शेष_sysctl_table
अणु
	काष्ठा ctl_table_header *sysctl_header;
	काष्ठा ctl_table vars[3];
	काष्ठा ctl_table शेष_dir[2];
	काष्ठा ctl_table parport_dir[2];
	काष्ठा ctl_table dev_dir[2];
पूर्ण;

अटल काष्ठा parport_शेष_sysctl_table
parport_शेष_sysctl_table = अणु
	.sysctl_header	= शून्य,
	अणु
		अणु
			.procname	= "timeslice",
			.data		= &parport_शेष_बारlice,
			.maxlen		= माप(parport_शेष_बारlice),
			.mode		= 0644,
			.proc_handler	= proc_करोuदीर्घvec_ms_jअगरfies_minmax,
			.extra1		= (व्योम*) &parport_min_बारlice_value,
			.extra2		= (व्योम*) &parport_max_बारlice_value
		पूर्ण,
		अणु
			.procname	= "spintime",
			.data		= &parport_शेष_spपूर्णांकime,
			.maxlen		= माप(parport_शेष_spपूर्णांकime),
			.mode		= 0644,
			.proc_handler	= proc_करोपूर्णांकvec_minmax,
			.extra1		= (व्योम*) &parport_min_spपूर्णांकime_value,
			.extra2		= (व्योम*) &parport_max_spपूर्णांकime_value
		पूर्ण,
		अणुपूर्ण
	पूर्ण,
	अणु
		अणु
			.procname	= "default",
			.mode		= 0555,
			.child		= parport_शेष_sysctl_table.vars
		पूर्ण,
		अणुपूर्ण
	पूर्ण,
	अणु
		PARPORT_PARPORT_सूची(parport_शेष_sysctl_table.शेष_dir),
		अणुपूर्ण
	पूर्ण,
	अणु
		PARPORT_DEV_सूची(parport_शेष_sysctl_table.parport_dir),
		अणुपूर्ण
	पूर्ण
पूर्ण;


पूर्णांक parport_proc_रेजिस्टर(काष्ठा parport *port)
अणु
	काष्ठा parport_sysctl_table *t;
	पूर्णांक i;

	t = kmemdup(&parport_sysctl_ढाँचा, माप(*t), GFP_KERNEL);
	अगर (t == शून्य)
		वापस -ENOMEM;

	t->device_dir[0].extra1 = port;

	क्रम (i = 0; i < 5; i++)
		t->vars[i].extra1 = port;

	t->vars[0].data = &port->spपूर्णांकime;
	t->vars[5].child = t->device_dir;
	
	क्रम (i = 0; i < 5; i++)
		t->vars[6 + i].extra2 = &port->probe_info[i];

	t->port_dir[0].procname = port->name;

	t->port_dir[0].child = t->vars;
	t->parport_dir[0].child = t->port_dir;
	t->dev_dir[0].child = t->parport_dir;

	t->sysctl_header = रेजिस्टर_sysctl_table(t->dev_dir);
	अगर (t->sysctl_header == शून्य) अणु
		kमुक्त(t);
		t = शून्य;
	पूर्ण
	port->sysctl_table = t;
	वापस 0;
पूर्ण

पूर्णांक parport_proc_unरेजिस्टर(काष्ठा parport *port)
अणु
	अगर (port->sysctl_table) अणु
		काष्ठा parport_sysctl_table *t = port->sysctl_table;
		port->sysctl_table = शून्य;
		unरेजिस्टर_sysctl_table(t->sysctl_header);
		kमुक्त(t);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक parport_device_proc_रेजिस्टर(काष्ठा pardevice *device)
अणु
	काष्ठा parport_device_sysctl_table *t;
	काष्ठा parport * port = device->port;
	
	t = kmemdup(&parport_device_sysctl_ढाँचा, माप(*t), GFP_KERNEL);
	अगर (t == शून्य)
		वापस -ENOMEM;

	t->dev_dir[0].child = t->parport_dir;
	t->parport_dir[0].child = t->port_dir;
	t->port_dir[0].procname = port->name;
	t->port_dir[0].child = t->devices_root_dir;
	t->devices_root_dir[0].child = t->device_dir;

	t->device_dir[0].procname = device->name;
	t->device_dir[0].child = t->vars;
	t->vars[0].data = &device->बारlice;

	t->sysctl_header = रेजिस्टर_sysctl_table(t->dev_dir);
	अगर (t->sysctl_header == शून्य) अणु
		kमुक्त(t);
		t = शून्य;
	पूर्ण
	device->sysctl_table = t;
	वापस 0;
पूर्ण

पूर्णांक parport_device_proc_unरेजिस्टर(काष्ठा pardevice *device)
अणु
	अगर (device->sysctl_table) अणु
		काष्ठा parport_device_sysctl_table *t = device->sysctl_table;
		device->sysctl_table = शून्य;
		unरेजिस्टर_sysctl_table(t->sysctl_header);
		kमुक्त(t);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init parport_शेष_proc_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret;

	parport_शेष_sysctl_table.sysctl_header =
		रेजिस्टर_sysctl_table(parport_शेष_sysctl_table.dev_dir);
	अगर (!parport_शेष_sysctl_table.sysctl_header)
		वापस -ENOMEM;
	ret = parport_bus_init();
	अगर (ret) अणु
		unरेजिस्टर_sysctl_table(parport_शेष_sysctl_table.
					sysctl_header);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास parport_शेष_proc_unरेजिस्टर(व्योम)
अणु
	अगर (parport_शेष_sysctl_table.sysctl_header) अणु
		unरेजिस्टर_sysctl_table(parport_शेष_sysctl_table.
					sysctl_header);
		parport_शेष_sysctl_table.sysctl_header = शून्य;
	पूर्ण
	parport_bus_निकास();
पूर्ण

#अन्यथा /* no sysctl or no procfs*/

पूर्णांक parport_proc_रेजिस्टर(काष्ठा parport *pp)
अणु
	वापस 0;
पूर्ण

पूर्णांक parport_proc_unरेजिस्टर(काष्ठा parport *pp)
अणु
	वापस 0;
पूर्ण

पूर्णांक parport_device_proc_रेजिस्टर(काष्ठा pardevice *device)
अणु
	वापस 0;
पूर्ण

पूर्णांक parport_device_proc_unरेजिस्टर(काष्ठा pardevice *device)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __init parport_शेष_proc_रेजिस्टर (व्योम)
अणु
	वापस parport_bus_init();
पूर्ण

अटल व्योम __निकास parport_शेष_proc_unरेजिस्टर (व्योम)
अणु
	parport_bus_निकास();
पूर्ण
#पूर्ण_अगर

subsys_initcall(parport_शेष_proc_रेजिस्टर)
module_निकास(parport_शेष_proc_unरेजिस्टर)
