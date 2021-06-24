<शैली गुरु>
/* 
        paride.c  (c) 1997-8  Grant R. Guenther <grant@torque.net>
                              Under the terms of the GNU General Public License.

	This is the base module क्रम the family of device drivers
        that support parallel port IDE devices.  

*/

/* Changes:

	1.01	GRG 1998.05.03	Use spinlocks
	1.02	GRG 1998.05.05  init_proto, release_proto, ktti
	1.03	GRG 1998.08.15  eliminate compiler warning
	1.04    GRG 1998.11.28  added support क्रम FRIQ 
	1.05    TMW 2000.06.06  use parport_find_number instead of
				parport_क्रमागतerate
	1.06    TMW 2001.03.26  more sane parport-or-not resource management
*/

#घोषणा PI_VERSION      "1.06"

#समावेश <linux/module.h>
#समावेश <linux/kmod.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>	/* TASK_* */
#समावेश <linux/parport.h>
#समावेश <linux/slab.h>

#समावेश "paride.h"

MODULE_LICENSE("GPL");

#घोषणा MAX_PROTOS	32

अटल काष्ठा pi_protocol *protocols[MAX_PROTOS];

अटल DEFINE_SPINLOCK(pi_spinlock);

व्योम pi_ग_लिखो_regr(PIA * pi, पूर्णांक cont, पूर्णांक regr, पूर्णांक val)
अणु
	pi->proto->ग_लिखो_regr(pi, cont, regr, val);
पूर्ण

EXPORT_SYMBOL(pi_ग_लिखो_regr);

पूर्णांक pi_पढ़ो_regr(PIA * pi, पूर्णांक cont, पूर्णांक regr)
अणु
	वापस pi->proto->पढ़ो_regr(pi, cont, regr);
पूर्ण

EXPORT_SYMBOL(pi_पढ़ो_regr);

व्योम pi_ग_लिखो_block(PIA * pi, अक्षर *buf, पूर्णांक count)
अणु
	pi->proto->ग_लिखो_block(pi, buf, count);
पूर्ण

EXPORT_SYMBOL(pi_ग_लिखो_block);

व्योम pi_पढ़ो_block(PIA * pi, अक्षर *buf, पूर्णांक count)
अणु
	pi->proto->पढ़ो_block(pi, buf, count);
पूर्ण

EXPORT_SYMBOL(pi_पढ़ो_block);

अटल व्योम pi_wake_up(व्योम *p)
अणु
	PIA *pi = (PIA *) p;
	अचिन्हित दीर्घ flags;
	व्योम (*cont) (व्योम) = शून्य;

	spin_lock_irqsave(&pi_spinlock, flags);

	अगर (pi->claim_cont && !parport_claim(pi->pardev)) अणु
		cont = pi->claim_cont;
		pi->claim_cont = शून्य;
		pi->claimed = 1;
	पूर्ण

	spin_unlock_irqrestore(&pi_spinlock, flags);

	wake_up(&(pi->parq));

	अगर (cont)
		cont();
पूर्ण

पूर्णांक pi_schedule_claimed(PIA * pi, व्योम (*cont) (व्योम))
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pi_spinlock, flags);
	अगर (pi->pardev && parport_claim(pi->pardev)) अणु
		pi->claim_cont = cont;
		spin_unlock_irqrestore(&pi_spinlock, flags);
		वापस 0;
	पूर्ण
	pi->claimed = 1;
	spin_unlock_irqrestore(&pi_spinlock, flags);
	वापस 1;
पूर्ण
EXPORT_SYMBOL(pi_schedule_claimed);

व्योम pi_करो_claimed(PIA * pi, व्योम (*cont) (व्योम))
अणु
	अगर (pi_schedule_claimed(pi, cont))
		cont();
पूर्ण

EXPORT_SYMBOL(pi_करो_claimed);

अटल व्योम pi_claim(PIA * pi)
अणु
	अगर (pi->claimed)
		वापस;
	pi->claimed = 1;
	अगर (pi->pardev)
		रुको_event(pi->parq,
			   !parport_claim((काष्ठा pardevice *) pi->pardev));
पूर्ण

अटल व्योम pi_unclaim(PIA * pi)
अणु
	pi->claimed = 0;
	अगर (pi->pardev)
		parport_release((काष्ठा pardevice *) (pi->pardev));
पूर्ण

व्योम pi_connect(PIA * pi)
अणु
	pi_claim(pi);
	pi->proto->connect(pi);
पूर्ण

EXPORT_SYMBOL(pi_connect);

व्योम pi_disconnect(PIA * pi)
अणु
	pi->proto->disconnect(pi);
	pi_unclaim(pi);
पूर्ण

EXPORT_SYMBOL(pi_disconnect);

अटल व्योम pi_unरेजिस्टर_parport(PIA * pi)
अणु
	अगर (pi->pardev) अणु
		parport_unरेजिस्टर_device((काष्ठा pardevice *) (pi->pardev));
		pi->pardev = शून्य;
	पूर्ण
पूर्ण

व्योम pi_release(PIA * pi)
अणु
	pi_unरेजिस्टर_parport(pi);
	अगर (pi->proto->release_proto)
		pi->proto->release_proto(pi);
	module_put(pi->proto->owner);
पूर्ण

EXPORT_SYMBOL(pi_release);

अटल पूर्णांक शेष_test_proto(PIA * pi, अक्षर *scratch, पूर्णांक verbose)
अणु
	पूर्णांक j, k;
	पूर्णांक e[2] = अणु 0, 0 पूर्ण;

	pi->proto->connect(pi);

	क्रम (j = 0; j < 2; j++) अणु
		pi_ग_लिखो_regr(pi, 0, 6, 0xa0 + j * 0x10);
		क्रम (k = 0; k < 256; k++) अणु
			pi_ग_लिखो_regr(pi, 0, 2, k ^ 0xaa);
			pi_ग_लिखो_regr(pi, 0, 3, k ^ 0x55);
			अगर (pi_पढ़ो_regr(pi, 0, 2) != (k ^ 0xaa))
				e[j]++;
		पूर्ण
	पूर्ण
	pi->proto->disconnect(pi);

	अगर (verbose)
		prपूर्णांकk("%s: %s: port 0x%x, mode  %d, test=(%d,%d)\n",
		       pi->device, pi->proto->name, pi->port,
		       pi->mode, e[0], e[1]);

	वापस (e[0] && e[1]);	/* not here अगर both > 0 */
पूर्ण

अटल पूर्णांक pi_test_proto(PIA * pi, अक्षर *scratch, पूर्णांक verbose)
अणु
	पूर्णांक res;

	pi_claim(pi);
	अगर (pi->proto->test_proto)
		res = pi->proto->test_proto(pi, scratch, verbose);
	अन्यथा
		res = शेष_test_proto(pi, scratch, verbose);
	pi_unclaim(pi);

	वापस res;
पूर्ण

पूर्णांक paride_रेजिस्टर(PIP * pr)
अणु
	पूर्णांक k;

	क्रम (k = 0; k < MAX_PROTOS; k++)
		अगर (protocols[k] && !म_भेद(pr->name, protocols[k]->name)) अणु
			prपूर्णांकk("paride: %s protocol already registered\n",
			       pr->name);
			वापस -1;
		पूर्ण
	k = 0;
	जबतक ((k < MAX_PROTOS) && (protocols[k]))
		k++;
	अगर (k == MAX_PROTOS) अणु
		prपूर्णांकk("paride: protocol table full\n");
		वापस -1;
	पूर्ण
	protocols[k] = pr;
	pr->index = k;
	prपूर्णांकk("paride: %s registered as protocol %d\n", pr->name, k);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(paride_रेजिस्टर);

व्योम paride_unरेजिस्टर(PIP * pr)
अणु
	अगर (!pr)
		वापस;
	अगर (protocols[pr->index] != pr) अणु
		prपूर्णांकk("paride: %s not registered\n", pr->name);
		वापस;
	पूर्ण
	protocols[pr->index] = शून्य;
पूर्ण

EXPORT_SYMBOL(paride_unरेजिस्टर);

अटल पूर्णांक pi_रेजिस्टर_parport(PIA *pi, पूर्णांक verbose, पूर्णांक unit)
अणु
	काष्ठा parport *port;
	काष्ठा pardev_cb par_cb;

	port = parport_find_base(pi->port);
	अगर (!port)
		वापस 0;
	स_रखो(&par_cb, 0, माप(par_cb));
	par_cb.wakeup = pi_wake_up;
	par_cb.निजी = (व्योम *)pi;
	pi->pardev = parport_रेजिस्टर_dev_model(port, pi->device, &par_cb,
						unit);
	parport_put_port(port);
	अगर (!pi->pardev)
		वापस 0;

	init_रुकोqueue_head(&pi->parq);

	अगर (verbose)
		prपूर्णांकk("%s: 0x%x is %s\n", pi->device, pi->port, port->name);

	pi->parname = (अक्षर *) port->name;

	वापस 1;
पूर्ण

अटल पूर्णांक pi_probe_mode(PIA * pi, पूर्णांक max, अक्षर *scratch, पूर्णांक verbose)
अणु
	पूर्णांक best, range;

	अगर (pi->mode != -1) अणु
		अगर (pi->mode >= max)
			वापस 0;
		range = 3;
		अगर (pi->mode >= pi->proto->epp_first)
			range = 8;
		अगर ((range == 8) && (pi->port % 8))
			वापस 0;
		pi->reserved = range;
		वापस (!pi_test_proto(pi, scratch, verbose));
	पूर्ण
	best = -1;
	क्रम (pi->mode = 0; pi->mode < max; pi->mode++) अणु
		range = 3;
		अगर (pi->mode >= pi->proto->epp_first)
			range = 8;
		अगर ((range == 8) && (pi->port % 8))
			अवरोध;
		pi->reserved = range;
		अगर (!pi_test_proto(pi, scratch, verbose))
			best = pi->mode;
	पूर्ण
	pi->mode = best;
	वापस (best > -1);
पूर्ण

अटल पूर्णांक pi_probe_unit(PIA * pi, पूर्णांक unit, अक्षर *scratch, पूर्णांक verbose)
अणु
	पूर्णांक max, s, e;

	s = unit;
	e = s + 1;

	अगर (s == -1) अणु
		s = 0;
		e = pi->proto->max_units;
	पूर्ण

	अगर (!pi_रेजिस्टर_parport(pi, verbose, s))
		वापस 0;

	अगर (pi->proto->test_port) अणु
		pi_claim(pi);
		max = pi->proto->test_port(pi);
		pi_unclaim(pi);
	पूर्ण अन्यथा
		max = pi->proto->max_mode;

	अगर (pi->proto->probe_unit) अणु
		pi_claim(pi);
		क्रम (pi->unit = s; pi->unit < e; pi->unit++)
			अगर (pi->proto->probe_unit(pi)) अणु
				pi_unclaim(pi);
				अगर (pi_probe_mode(pi, max, scratch, verbose))
					वापस 1;
				pi_unरेजिस्टर_parport(pi);
				वापस 0;
			पूर्ण
		pi_unclaim(pi);
		pi_unरेजिस्टर_parport(pi);
		वापस 0;
	पूर्ण

	अगर (!pi_probe_mode(pi, max, scratch, verbose)) अणु
		pi_unरेजिस्टर_parport(pi);
		वापस 0;
	पूर्ण
	वापस 1;

पूर्ण

पूर्णांक pi_init(PIA * pi, पूर्णांक स्वतःprobe, पूर्णांक port, पूर्णांक mode,
	पूर्णांक unit, पूर्णांक protocol, पूर्णांक delay, अक्षर *scratch,
	पूर्णांक devtype, पूर्णांक verbose, अक्षर *device)
अणु
	पूर्णांक p, k, s, e;
	पूर्णांक lpts[7] = अणु 0x3bc, 0x378, 0x278, 0x268, 0x27c, 0x26c, 0 पूर्ण;

	s = protocol;
	e = s + 1;

	अगर (!protocols[0])
		request_module("paride_protocol");

	अगर (स्वतःprobe) अणु
		s = 0;
		e = MAX_PROTOS;
	पूर्ण अन्यथा अगर ((s < 0) || (s >= MAX_PROTOS) || (port <= 0) ||
		   (!protocols[s]) || (unit < 0) ||
		   (unit >= protocols[s]->max_units)) अणु
		prपूर्णांकk("%s: Invalid parameters\n", device);
		वापस 0;
	पूर्ण

	क्रम (p = s; p < e; p++) अणु
		काष्ठा pi_protocol *proto = protocols[p];
		अगर (!proto)
			जारी;
		/* still racy */
		अगर (!try_module_get(proto->owner))
			जारी;
		pi->proto = proto;
		pi->निजी = 0;
		अगर (proto->init_proto && proto->init_proto(pi) < 0) अणु
			pi->proto = शून्य;
			module_put(proto->owner);
			जारी;
		पूर्ण
		अगर (delay == -1)
			pi->delay = pi->proto->शेष_delay;
		अन्यथा
			pi->delay = delay;
		pi->devtype = devtype;
		pi->device = device;

		pi->parname = शून्य;
		pi->pardev = शून्य;
		init_रुकोqueue_head(&pi->parq);
		pi->claimed = 0;
		pi->claim_cont = शून्य;

		pi->mode = mode;
		अगर (port != -1) अणु
			pi->port = port;
			अगर (pi_probe_unit(pi, unit, scratch, verbose))
				अवरोध;
			pi->port = 0;
		पूर्ण अन्यथा अणु
			k = 0;
			जबतक ((pi->port = lpts[k++]))
				अगर (pi_probe_unit
				    (pi, unit, scratch, verbose))
					अवरोध;
			अगर (pi->port)
				अवरोध;
		पूर्ण
		अगर (pi->proto->release_proto)
			pi->proto->release_proto(pi);
		module_put(proto->owner);
	पूर्ण

	अगर (!pi->port) अणु
		अगर (स्वतःprobe)
			prपूर्णांकk("%s: Autoprobe failed\n", device);
		अन्यथा
			prपूर्णांकk("%s: Adapter not found\n", device);
		वापस 0;
	पूर्ण

	अगर (pi->parname)
		prपूर्णांकk("%s: Sharing %s at 0x%x\n", pi->device,
		       pi->parname, pi->port);

	pi->proto->log_adapter(pi, scratch, verbose);

	वापस 1;
पूर्ण

EXPORT_SYMBOL(pi_init);

अटल पूर्णांक pi_probe(काष्ठा pardevice *par_dev)
अणु
	काष्ठा device_driver *drv = par_dev->dev.driver;
	पूर्णांक len = म_माप(drv->name);

	अगर (म_भेदन(par_dev->name, drv->name, len))
		वापस -ENODEV;

	वापस 0;
पूर्ण

व्योम *pi_रेजिस्टर_driver(अक्षर *name)
अणु
	काष्ठा parport_driver *parp_drv;
	पूर्णांक ret;

	parp_drv = kzalloc(माप(*parp_drv), GFP_KERNEL);
	अगर (!parp_drv)
		वापस शून्य;

	parp_drv->name = name;
	parp_drv->probe = pi_probe;
	parp_drv->devmodel = true;

	ret = parport_रेजिस्टर_driver(parp_drv);
	अगर (ret) अणु
		kमुक्त(parp_drv);
		वापस शून्य;
	पूर्ण
	वापस (व्योम *)parp_drv;
पूर्ण
EXPORT_SYMBOL(pi_रेजिस्टर_driver);

व्योम pi_unरेजिस्टर_driver(व्योम *_drv)
अणु
	काष्ठा parport_driver *drv = _drv;

	parport_unरेजिस्टर_driver(drv);
	kमुक्त(drv);
पूर्ण
EXPORT_SYMBOL(pi_unरेजिस्टर_driver);
