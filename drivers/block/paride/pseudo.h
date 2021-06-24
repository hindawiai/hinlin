<शैली गुरु>
/* 
        pseuकरो.h    (c) 1997-8  Grant R. Guenther <grant@torque.net>
                                Under the terms of the GNU General Public License.

	This is the "pseudo-interrupt" logic क्रम parallel port drivers.

        This module is #समावेशd पूर्णांकo each driver.  It makes one
        function available:

		ps_set_पूर्णांकr( व्योम (*continuation)(व्योम),
			     पूर्णांक  (*पढ़ोy)(व्योम),
			     पूर्णांक समयout,
			     पूर्णांक nice )

	Which will arrange क्रम पढ़ोy() to be evaluated frequently and
	when either it वापसs true, or समयout jअगरfies have passed,
	continuation() will be invoked.

	If nice is 1, the test will करोne approximately once a
	jअगरfy.  If nice is 0, the test will also be करोne whenever
	the scheduler runs (by adding it to a task queue).  If
	nice is greater than 1, the test will be करोne once every
	(nice-1) jअगरfies. 

*/

/* Changes:

	1.01	1998.05.03	Switched from cli()/sti() to spinlocks
	1.02    1998.12.14      Added support क्रम nice > 1
*/
	
#घोषणा PS_VERSION	"1.02"

#समावेश <linux/sched.h>
#समावेश <linux/workqueue.h>

अटल व्योम ps_tq_पूर्णांक(काष्ठा work_काष्ठा *work);

अटल व्योम (* ps_continuation)(व्योम);
अटल पूर्णांक (* ps_पढ़ोy)(व्योम);
अटल अचिन्हित दीर्घ ps_समयout;
अटल पूर्णांक ps_tq_active = 0;
अटल पूर्णांक ps_nice = 0;

अटल DEFINE_SPINLOCK(ps_spinlock __attribute__((unused)));

अटल DECLARE_DELAYED_WORK(ps_tq, ps_tq_पूर्णांक);

अटल व्योम ps_set_पूर्णांकr(व्योम (*continuation)(व्योम), 
			पूर्णांक (*पढ़ोy)(व्योम),
			पूर्णांक समयout, पूर्णांक nice)
अणु
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&ps_spinlock,flags);

	ps_continuation = continuation;
	ps_पढ़ोy = पढ़ोy;
	ps_समयout = jअगरfies + समयout;
	ps_nice = nice;

	अगर (!ps_tq_active) अणु
		ps_tq_active = 1;
		अगर (!ps_nice)
			schedule_delayed_work(&ps_tq, 0);
		अन्यथा
			schedule_delayed_work(&ps_tq, ps_nice-1);
	पूर्ण
	spin_unlock_irqrestore(&ps_spinlock,flags);
पूर्ण

अटल व्योम ps_tq_पूर्णांक(काष्ठा work_काष्ठा *work)
अणु
	व्योम (*con)(व्योम);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ps_spinlock,flags);

	con = ps_continuation;
	ps_tq_active = 0;

	अगर (!con) अणु
		spin_unlock_irqrestore(&ps_spinlock,flags);
		वापस;
	पूर्ण
	अगर (!ps_पढ़ोy || ps_पढ़ोy() || समय_after_eq(jअगरfies, ps_समयout)) अणु
		ps_continuation = शून्य;
		spin_unlock_irqrestore(&ps_spinlock,flags);
		con();
		वापस;
	पूर्ण
	ps_tq_active = 1;
	अगर (!ps_nice)
		schedule_delayed_work(&ps_tq, 0);
	अन्यथा
		schedule_delayed_work(&ps_tq, ps_nice-1);
	spin_unlock_irqrestore(&ps_spinlock,flags);
पूर्ण

/* end of pseuकरो.h */

