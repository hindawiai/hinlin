<शैली गुरु>
/* $Id: kcapi.c,v 1.1.2.8 2004/03/26 19:57:20 armin Exp $
 *
 * Kernel CAPI 2.0 Module
 *
 * Copyright 1999 by Carsten Paeth <calle@calle.de>
 * Copyright 2002 by Kai Germaschewski <kai@germaschewski.name>
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#समावेश "kcapi.h"
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/capi.h>
#समावेश <linux/kernelcapi.h>
#समावेश <linux/init.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/isdn/capicmd.h>
#समावेश <linux/isdn/capiutil.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rcupdate.h>

अटल पूर्णांक showcapimsgs = 0;
अटल काष्ठा workqueue_काष्ठा *kcapi_wq;

module_param(showcapimsgs, uपूर्णांक, 0);

/* ------------------------------------------------------------- */

काष्ठा capictr_event अणु
	काष्ठा work_काष्ठा work;
	अचिन्हित पूर्णांक type;
	u32 controller;
पूर्ण;

/* ------------------------------------------------------------- */

अटल स्थिर काष्ठा capi_version driver_version = अणु2, 0, 1, 1 << 4पूर्ण;
अटल अक्षर driver_serial[CAPI_SERIAL_LEN] = "0004711";
अटल अक्षर capi_manufakturer[64] = "AVM Berlin";

#घोषणा NCCI2CTRL(ncci)    (((ncci) >> 24) & 0x7f)

काष्ठा capi_ctr *capi_controller[CAPI_MAXCONTR];
DEFINE_MUTEX(capi_controller_lock);

काष्ठा capi20_appl *capi_applications[CAPI_MAXAPPL];

अटल पूर्णांक ncontrollers;

/* -------- controller ref counting -------------------------------------- */

अटल अंतरभूत काष्ठा capi_ctr *
capi_ctr_get(काष्ठा capi_ctr *ctr)
अणु
	अगर (!try_module_get(ctr->owner))
		वापस शून्य;
	वापस ctr;
पूर्ण

अटल अंतरभूत व्योम
capi_ctr_put(काष्ठा capi_ctr *ctr)
अणु
	module_put(ctr->owner);
पूर्ण

/* ------------------------------------------------------------- */

अटल अंतरभूत काष्ठा capi_ctr *get_capi_ctr_by_nr(u16 contr)
अणु
	अगर (contr < 1 || contr - 1 >= CAPI_MAXCONTR)
		वापस शून्य;

	वापस capi_controller[contr - 1];
पूर्ण

अटल अंतरभूत काष्ठा capi20_appl *__get_capi_appl_by_nr(u16 applid)
अणु
	lockdep_निश्चित_held(&capi_controller_lock);

	अगर (applid < 1 || applid - 1 >= CAPI_MAXAPPL)
		वापस शून्य;

	वापस capi_applications[applid - 1];
पूर्ण

अटल अंतरभूत काष्ठा capi20_appl *get_capi_appl_by_nr(u16 applid)
अणु
	अगर (applid < 1 || applid - 1 >= CAPI_MAXAPPL)
		वापस शून्य;

	वापस rcu_dereference(capi_applications[applid - 1]);
पूर्ण

/* -------- util functions ------------------------------------ */

अटल अंतरभूत पूर्णांक capi_cmd_valid(u8 cmd)
अणु
	चयन (cmd) अणु
	हाल CAPI_ALERT:
	हाल CAPI_CONNECT:
	हाल CAPI_CONNECT_ACTIVE:
	हाल CAPI_CONNECT_B3_ACTIVE:
	हाल CAPI_CONNECT_B3:
	हाल CAPI_CONNECT_B3_T90_ACTIVE:
	हाल CAPI_DATA_B3:
	हाल CAPI_DISCONNECT_B3:
	हाल CAPI_DISCONNECT:
	हाल CAPI_FACILITY:
	हाल CAPI_INFO:
	हाल CAPI_LISTEN:
	हाल CAPI_MANUFACTURER:
	हाल CAPI_RESET_B3:
	हाल CAPI_SELECT_B_PROTOCOL:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक capi_subcmd_valid(u8 subcmd)
अणु
	चयन (subcmd) अणु
	हाल CAPI_REQ:
	हाल CAPI_CONF:
	हाल CAPI_IND:
	हाल CAPI_RESP:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* ------------------------------------------------------------ */

अटल व्योम
रेजिस्टर_appl(काष्ठा capi_ctr *ctr, u16 applid, capi_रेजिस्टर_params *rparam)
अणु
	ctr = capi_ctr_get(ctr);

	अगर (ctr)
		ctr->रेजिस्टर_appl(ctr, applid, rparam);
	अन्यथा
		prपूर्णांकk(KERN_WARNING "%s: cannot get controller resources\n",
		       __func__);
पूर्ण


अटल व्योम release_appl(काष्ठा capi_ctr *ctr, u16 applid)
अणु
	DBG("applid %#x", applid);

	ctr->release_appl(ctr, applid);
	capi_ctr_put(ctr);
पूर्ण

अटल व्योम notअगरy_up(u32 contr)
अणु
	काष्ठा capi20_appl *ap;
	काष्ठा capi_ctr *ctr;
	u16 applid;

	mutex_lock(&capi_controller_lock);

	अगर (showcapimsgs & 1)
		prपूर्णांकk(KERN_DEBUG "kcapi: notify up contr %d\n", contr);

	ctr = get_capi_ctr_by_nr(contr);
	अगर (ctr) अणु
		अगर (ctr->state == CAPI_CTR_RUNNING)
			जाओ unlock_out;

		ctr->state = CAPI_CTR_RUNNING;

		क्रम (applid = 1; applid <= CAPI_MAXAPPL; applid++) अणु
			ap = __get_capi_appl_by_nr(applid);
			अगर (ap)
				रेजिस्टर_appl(ctr, applid, &ap->rparam);
		पूर्ण
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_WARNING "%s: invalid contr %d\n", __func__, contr);

unlock_out:
	mutex_unlock(&capi_controller_lock);
पूर्ण

अटल व्योम ctr_करोwn(काष्ठा capi_ctr *ctr, पूर्णांक new_state)
अणु
	काष्ठा capi20_appl *ap;
	u16 applid;

	अगर (ctr->state == CAPI_CTR_DETECTED || ctr->state == CAPI_CTR_DETACHED)
		वापस;

	ctr->state = new_state;

	स_रखो(ctr->manu, 0, माप(ctr->manu));
	स_रखो(&ctr->version, 0, माप(ctr->version));
	स_रखो(&ctr->profile, 0, माप(ctr->profile));
	स_रखो(ctr->serial, 0, माप(ctr->serial));

	क्रम (applid = 1; applid <= CAPI_MAXAPPL; applid++) अणु
		ap = __get_capi_appl_by_nr(applid);
		अगर (ap)
			capi_ctr_put(ctr);
	पूर्ण
पूर्ण

अटल व्योम notअगरy_करोwn(u32 contr)
अणु
	काष्ठा capi_ctr *ctr;

	mutex_lock(&capi_controller_lock);

	अगर (showcapimsgs & 1)
		prपूर्णांकk(KERN_DEBUG "kcapi: notify down contr %d\n", contr);

	ctr = get_capi_ctr_by_nr(contr);
	अगर (ctr)
		ctr_करोwn(ctr, CAPI_CTR_DETECTED);
	अन्यथा
		prपूर्णांकk(KERN_WARNING "%s: invalid contr %d\n", __func__, contr);

	mutex_unlock(&capi_controller_lock);
पूर्ण

अटल व्योम करो_notअगरy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा capictr_event *event =
		container_of(work, काष्ठा capictr_event, work);

	चयन (event->type) अणु
	हाल CAPICTR_UP:
		notअगरy_up(event->controller);
		अवरोध;
	हाल CAPICTR_DOWN:
		notअगरy_करोwn(event->controller);
		अवरोध;
	पूर्ण

	kमुक्त(event);
पूर्ण

अटल पूर्णांक notअगरy_push(अचिन्हित पूर्णांक event_type, u32 controller)
अणु
	काष्ठा capictr_event *event = kदो_स्मृति(माप(*event), GFP_ATOMIC);

	अगर (!event)
		वापस -ENOMEM;

	INIT_WORK(&event->work, करो_notअगरy_work);
	event->type = event_type;
	event->controller = controller;

	queue_work(kcapi_wq, &event->work);
	वापस 0;
पूर्ण

/* -------- Receiver ------------------------------------------ */

अटल व्योम recv_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा capi20_appl *ap =
		container_of(work, काष्ठा capi20_appl, recv_work);

	अगर ((!ap) || (ap->release_in_progress))
		वापस;

	mutex_lock(&ap->recv_mtx);
	जबतक ((skb = skb_dequeue(&ap->recv_queue))) अणु
		अगर (CAPIMSG_CMD(skb->data) == CAPI_DATA_B3_IND)
			ap->nrecvdatapkt++;
		अन्यथा
			ap->nrecvctlpkt++;

		ap->recv_message(ap, skb);
	पूर्ण
	mutex_unlock(&ap->recv_mtx);
पूर्ण

/**
 * capi_ctr_handle_message() - handle incoming CAPI message
 * @ctr:	controller descriptor काष्ठाure.
 * @appl:	application ID.
 * @skb:	message.
 *
 * Called by hardware driver to pass a CAPI message to the application.
 */

व्योम capi_ctr_handle_message(काष्ठा capi_ctr *ctr, u16 appl,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा capi20_appl *ap;
	पूर्णांक showctl = 0;
	u8 cmd, subcmd;
	_cdebbuf *cdb;

	अगर (ctr->state != CAPI_CTR_RUNNING) अणु
		cdb = capi_message2str(skb->data);
		अगर (cdb) अणु
			prपूर्णांकk(KERN_INFO "kcapi: controller [%03d] not active, got: %s",
			       ctr->cnr, cdb->buf);
			cdebbuf_मुक्त(cdb);
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_INFO "kcapi: controller [%03d] not active, cannot trace\n",
			       ctr->cnr);
		जाओ error;
	पूर्ण

	cmd = CAPIMSG_COMMAND(skb->data);
	subcmd = CAPIMSG_SUBCOMMAND(skb->data);
	अगर (cmd == CAPI_DATA_B3 && subcmd == CAPI_IND) अणु
		ctr->nrecvdatapkt++;
		अगर (ctr->traceflag > 2)
			showctl |= 2;
	पूर्ण अन्यथा अणु
		ctr->nrecvctlpkt++;
		अगर (ctr->traceflag)
			showctl |= 2;
	पूर्ण
	showctl |= (ctr->traceflag & 1);
	अगर (showctl & 2) अणु
		अगर (showctl & 1) अणु
			prपूर्णांकk(KERN_DEBUG "kcapi: got [%03d] id#%d %s len=%u\n",
			       ctr->cnr, CAPIMSG_APPID(skb->data),
			       capi_cmd2str(cmd, subcmd),
			       CAPIMSG_LEN(skb->data));
		पूर्ण अन्यथा अणु
			cdb = capi_message2str(skb->data);
			अगर (cdb) अणु
				prपूर्णांकk(KERN_DEBUG "kcapi: got [%03d] %s\n",
				       ctr->cnr, cdb->buf);
				cdebbuf_मुक्त(cdb);
			पूर्ण अन्यथा
				prपूर्णांकk(KERN_DEBUG "kcapi: got [%03d] id#%d %s len=%u, cannot trace\n",
				       ctr->cnr, CAPIMSG_APPID(skb->data),
				       capi_cmd2str(cmd, subcmd),
				       CAPIMSG_LEN(skb->data));
		पूर्ण

	पूर्ण

	rcu_पढ़ो_lock();
	ap = get_capi_appl_by_nr(CAPIMSG_APPID(skb->data));
	अगर (!ap) अणु
		rcu_पढ़ो_unlock();
		cdb = capi_message2str(skb->data);
		अगर (cdb) अणु
			prपूर्णांकk(KERN_ERR "kcapi: handle_message: applid %d state released (%s)\n",
			       CAPIMSG_APPID(skb->data), cdb->buf);
			cdebbuf_मुक्त(cdb);
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_ERR "kcapi: handle_message: applid %d state released (%s) cannot trace\n",
			       CAPIMSG_APPID(skb->data),
			       capi_cmd2str(cmd, subcmd));
		जाओ error;
	पूर्ण
	skb_queue_tail(&ap->recv_queue, skb);
	queue_work(kcapi_wq, &ap->recv_work);
	rcu_पढ़ो_unlock();

	वापस;

error:
	kमुक्त_skb(skb);
पूर्ण

EXPORT_SYMBOL(capi_ctr_handle_message);

/**
 * capi_ctr_पढ़ोy() - संकेत CAPI controller पढ़ोy
 * @ctr:	controller descriptor काष्ठाure.
 *
 * Called by hardware driver to संकेत that the controller is up and running.
 */

व्योम capi_ctr_पढ़ोy(काष्ठा capi_ctr *ctr)
अणु
	prपूर्णांकk(KERN_NOTICE "kcapi: controller [%03d] \"%s\" ready.\n",
	       ctr->cnr, ctr->name);

	notअगरy_push(CAPICTR_UP, ctr->cnr);
पूर्ण

EXPORT_SYMBOL(capi_ctr_पढ़ोy);

/**
 * capi_ctr_करोwn() - संकेत CAPI controller not पढ़ोy
 * @ctr:	controller descriptor काष्ठाure.
 *
 * Called by hardware driver to संकेत that the controller is करोwn and
 * unavailable क्रम use.
 */

व्योम capi_ctr_करोwn(काष्ठा capi_ctr *ctr)
अणु
	prपूर्णांकk(KERN_NOTICE "kcapi: controller [%03d] down.\n", ctr->cnr);

	notअगरy_push(CAPICTR_DOWN, ctr->cnr);
पूर्ण

EXPORT_SYMBOL(capi_ctr_करोwn);

/* ------------------------------------------------------------- */

/**
 * attach_capi_ctr() - रेजिस्टर CAPI controller
 * @ctr:	controller descriptor काष्ठाure.
 *
 * Called by hardware driver to रेजिस्टर a controller with the CAPI subप्रणाली.
 * Return value: 0 on success, error code < 0 on error
 */

पूर्णांक attach_capi_ctr(काष्ठा capi_ctr *ctr)
अणु
	पूर्णांक i;

	mutex_lock(&capi_controller_lock);

	क्रम (i = 0; i < CAPI_MAXCONTR; i++) अणु
		अगर (!capi_controller[i])
			अवरोध;
	पूर्ण
	अगर (i == CAPI_MAXCONTR) अणु
		mutex_unlock(&capi_controller_lock);
		prपूर्णांकk(KERN_ERR "kcapi: out of controller slots\n");
		वापस -EBUSY;
	पूर्ण
	capi_controller[i] = ctr;

	ctr->nrecvctlpkt = 0;
	ctr->nrecvdatapkt = 0;
	ctr->nsentctlpkt = 0;
	ctr->nsentdatapkt = 0;
	ctr->cnr = i + 1;
	ctr->state = CAPI_CTR_DETECTED;
	ctr->blocked = 0;
	ctr->traceflag = showcapimsgs;

	प्र_लिखो(ctr->procfn, "capi/controllers/%d", ctr->cnr);
	ctr->procent = proc_create_single_data(ctr->procfn, 0, शून्य,
			ctr->proc_show, ctr);

	ncontrollers++;

	mutex_unlock(&capi_controller_lock);

	prपूर्णांकk(KERN_NOTICE "kcapi: controller [%03d]: %s attached\n",
	       ctr->cnr, ctr->name);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(attach_capi_ctr);

/**
 * detach_capi_ctr() - unरेजिस्टर CAPI controller
 * @ctr:	controller descriptor काष्ठाure.
 *
 * Called by hardware driver to हटाओ the registration of a controller
 * with the CAPI subप्रणाली.
 * Return value: 0 on success, error code < 0 on error
 */

पूर्णांक detach_capi_ctr(काष्ठा capi_ctr *ctr)
अणु
	पूर्णांक err = 0;

	mutex_lock(&capi_controller_lock);

	ctr_करोwn(ctr, CAPI_CTR_DETACHED);

	अगर (capi_controller[ctr->cnr - 1] != ctr) अणु
		err = -EINVAL;
		जाओ unlock_out;
	पूर्ण
	capi_controller[ctr->cnr - 1] = शून्य;
	ncontrollers--;

	अगर (ctr->procent)
		हटाओ_proc_entry(ctr->procfn, शून्य);

	prपूर्णांकk(KERN_NOTICE "kcapi: controller [%03d]: %s unregistered\n",
	       ctr->cnr, ctr->name);

unlock_out:
	mutex_unlock(&capi_controller_lock);

	वापस err;
पूर्ण

EXPORT_SYMBOL(detach_capi_ctr);

/* ------------------------------------------------------------- */
/* -------- CAPI2.0 Interface ---------------------------------- */
/* ------------------------------------------------------------- */

/**
 * capi20_isinstalled() - CAPI 2.0 operation CAPI_INSTALLED
 *
 * Return value: CAPI result code (CAPI_NOERROR अगर at least one ISDN controller
 *	is पढ़ोy क्रम use, CAPI_REGNOTINSTALLED otherwise)
 */

u16 capi20_isinstalled(व्योम)
अणु
	u16 ret = CAPI_REGNOTINSTALLED;
	पूर्णांक i;

	mutex_lock(&capi_controller_lock);

	क्रम (i = 0; i < CAPI_MAXCONTR; i++)
		अगर (capi_controller[i] &&
		    capi_controller[i]->state == CAPI_CTR_RUNNING) अणु
			ret = CAPI_NOERROR;
			अवरोध;
		पूर्ण

	mutex_unlock(&capi_controller_lock);

	वापस ret;
पूर्ण

/**
 * capi20_रेजिस्टर() - CAPI 2.0 operation CAPI_REGISTER
 * @ap:		CAPI application descriptor काष्ठाure.
 *
 * Register an application's presence with CAPI.
 * A unique application ID is asचिन्हित and stored in @ap->applid.
 * After this function वापसs successfully, the message receive
 * callback function @ap->recv_message() may be called at any समय
 * until capi20_release() has been called क्रम the same @ap.
 * Return value: CAPI result code
 */

u16 capi20_रेजिस्टर(काष्ठा capi20_appl *ap)
अणु
	पूर्णांक i;
	u16 applid;

	DBG("");

	अगर (ap->rparam.datablklen < 128)
		वापस CAPI_LOGBLKSIZETOSMALL;

	ap->nrecvctlpkt = 0;
	ap->nrecvdatapkt = 0;
	ap->nsentctlpkt = 0;
	ap->nsentdatapkt = 0;
	mutex_init(&ap->recv_mtx);
	skb_queue_head_init(&ap->recv_queue);
	INIT_WORK(&ap->recv_work, recv_handler);
	ap->release_in_progress = 0;

	mutex_lock(&capi_controller_lock);

	क्रम (applid = 1; applid <= CAPI_MAXAPPL; applid++) अणु
		अगर (capi_applications[applid - 1] == शून्य)
			अवरोध;
	पूर्ण
	अगर (applid > CAPI_MAXAPPL) अणु
		mutex_unlock(&capi_controller_lock);
		वापस CAPI_TOOMANYAPPLS;
	पूर्ण

	ap->applid = applid;
	capi_applications[applid - 1] = ap;

	क्रम (i = 0; i < CAPI_MAXCONTR; i++) अणु
		अगर (!capi_controller[i] ||
		    capi_controller[i]->state != CAPI_CTR_RUNNING)
			जारी;
		रेजिस्टर_appl(capi_controller[i], applid, &ap->rparam);
	पूर्ण

	mutex_unlock(&capi_controller_lock);

	अगर (showcapimsgs & 1) अणु
		prपूर्णांकk(KERN_DEBUG "kcapi: appl %d up\n", applid);
	पूर्ण

	वापस CAPI_NOERROR;
पूर्ण

/**
 * capi20_release() - CAPI 2.0 operation CAPI_RELEASE
 * @ap:		CAPI application descriptor काष्ठाure.
 *
 * Terminate an application's registration with CAPI.
 * After this function वापसs successfully, the message receive
 * callback function @ap->recv_message() will no दीर्घer be called.
 * Return value: CAPI result code
 */

u16 capi20_release(काष्ठा capi20_appl *ap)
अणु
	पूर्णांक i;

	DBG("applid %#x", ap->applid);

	mutex_lock(&capi_controller_lock);

	ap->release_in_progress = 1;
	capi_applications[ap->applid - 1] = शून्य;

	synchronize_rcu();

	क्रम (i = 0; i < CAPI_MAXCONTR; i++) अणु
		अगर (!capi_controller[i] ||
		    capi_controller[i]->state != CAPI_CTR_RUNNING)
			जारी;
		release_appl(capi_controller[i], ap->applid);
	पूर्ण

	mutex_unlock(&capi_controller_lock);

	flush_workqueue(kcapi_wq);
	skb_queue_purge(&ap->recv_queue);

	अगर (showcapimsgs & 1) अणु
		prपूर्णांकk(KERN_DEBUG "kcapi: appl %d down\n", ap->applid);
	पूर्ण

	वापस CAPI_NOERROR;
पूर्ण

/**
 * capi20_put_message() - CAPI 2.0 operation CAPI_PUT_MESSAGE
 * @ap:		CAPI application descriptor काष्ठाure.
 * @skb:	CAPI message.
 *
 * Transfer a single message to CAPI.
 * Return value: CAPI result code
 */

u16 capi20_put_message(काष्ठा capi20_appl *ap, काष्ठा sk_buff *skb)
अणु
	काष्ठा capi_ctr *ctr;
	पूर्णांक showctl = 0;
	u8 cmd, subcmd;

	DBG("applid %#x", ap->applid);

	अगर (ncontrollers == 0)
		वापस CAPI_REGNOTINSTALLED;
	अगर ((ap->applid == 0) || ap->release_in_progress)
		वापस CAPI_ILLAPPNR;
	अगर (skb->len < 12
	    || !capi_cmd_valid(CAPIMSG_COMMAND(skb->data))
	    || !capi_subcmd_valid(CAPIMSG_SUBCOMMAND(skb->data)))
		वापस CAPI_ILLCMDORSUBCMDORMSGTOSMALL;

	/*
	 * The controller reference is रक्षित by the existence of the
	 * application passed to us. We assume that the caller properly
	 * synchronizes this service with capi20_release.
	 */
	ctr = get_capi_ctr_by_nr(CAPIMSG_CONTROLLER(skb->data));
	अगर (!ctr || ctr->state != CAPI_CTR_RUNNING)
		वापस CAPI_REGNOTINSTALLED;
	अगर (ctr->blocked)
		वापस CAPI_SENDQUEUEFULL;

	cmd = CAPIMSG_COMMAND(skb->data);
	subcmd = CAPIMSG_SUBCOMMAND(skb->data);

	अगर (cmd == CAPI_DATA_B3 && subcmd == CAPI_REQ) अणु
		ctr->nsentdatapkt++;
		ap->nsentdatapkt++;
		अगर (ctr->traceflag > 2)
			showctl |= 2;
	पूर्ण अन्यथा अणु
		ctr->nsentctlpkt++;
		ap->nsentctlpkt++;
		अगर (ctr->traceflag)
			showctl |= 2;
	पूर्ण
	showctl |= (ctr->traceflag & 1);
	अगर (showctl & 2) अणु
		अगर (showctl & 1) अणु
			prपूर्णांकk(KERN_DEBUG "kcapi: put [%03d] id#%d %s len=%u\n",
			       CAPIMSG_CONTROLLER(skb->data),
			       CAPIMSG_APPID(skb->data),
			       capi_cmd2str(cmd, subcmd),
			       CAPIMSG_LEN(skb->data));
		पूर्ण अन्यथा अणु
			_cdebbuf *cdb = capi_message2str(skb->data);
			अगर (cdb) अणु
				prपूर्णांकk(KERN_DEBUG "kcapi: put [%03d] %s\n",
				       CAPIMSG_CONTROLLER(skb->data),
				       cdb->buf);
				cdebbuf_मुक्त(cdb);
			पूर्ण अन्यथा
				prपूर्णांकk(KERN_DEBUG "kcapi: put [%03d] id#%d %s len=%u cannot trace\n",
				       CAPIMSG_CONTROLLER(skb->data),
				       CAPIMSG_APPID(skb->data),
				       capi_cmd2str(cmd, subcmd),
				       CAPIMSG_LEN(skb->data));
		पूर्ण
	पूर्ण
	वापस ctr->send_message(ctr, skb);
पूर्ण

/**
 * capi20_get_manufacturer() - CAPI 2.0 operation CAPI_GET_MANUFACTURER
 * @contr:	controller number.
 * @buf:	result buffer (64 bytes).
 *
 * Retrieve inक्रमmation about the manufacturer of the specअगरied ISDN controller
 * or (क्रम @contr == 0) the driver itself.
 * Return value: CAPI result code
 */

u16 capi20_get_manufacturer(u32 contr, u8 buf[CAPI_MANUFACTURER_LEN])
अणु
	काष्ठा capi_ctr *ctr;
	u16 ret;

	अगर (contr == 0) अणु
		म_नकलन(buf, capi_manufakturer, CAPI_MANUFACTURER_LEN);
		वापस CAPI_NOERROR;
	पूर्ण

	mutex_lock(&capi_controller_lock);

	ctr = get_capi_ctr_by_nr(contr);
	अगर (ctr && ctr->state == CAPI_CTR_RUNNING) अणु
		म_नकलन(buf, ctr->manu, CAPI_MANUFACTURER_LEN);
		ret = CAPI_NOERROR;
	पूर्ण अन्यथा
		ret = CAPI_REGNOTINSTALLED;

	mutex_unlock(&capi_controller_lock);
	वापस ret;
पूर्ण

/**
 * capi20_get_version() - CAPI 2.0 operation CAPI_GET_VERSION
 * @contr:	controller number.
 * @verp:	result काष्ठाure.
 *
 * Retrieve version inक्रमmation क्रम the specअगरied ISDN controller
 * or (क्रम @contr == 0) the driver itself.
 * Return value: CAPI result code
 */

u16 capi20_get_version(u32 contr, काष्ठा capi_version *verp)
अणु
	काष्ठा capi_ctr *ctr;
	u16 ret;

	अगर (contr == 0) अणु
		*verp = driver_version;
		वापस CAPI_NOERROR;
	पूर्ण

	mutex_lock(&capi_controller_lock);

	ctr = get_capi_ctr_by_nr(contr);
	अगर (ctr && ctr->state == CAPI_CTR_RUNNING) अणु
		स_नकल(verp, &ctr->version, माप(capi_version));
		ret = CAPI_NOERROR;
	पूर्ण अन्यथा
		ret = CAPI_REGNOTINSTALLED;

	mutex_unlock(&capi_controller_lock);
	वापस ret;
पूर्ण

/**
 * capi20_get_serial() - CAPI 2.0 operation CAPI_GET_SERIAL_NUMBER
 * @contr:	controller number.
 * @serial:	result buffer (8 bytes).
 *
 * Retrieve the serial number of the specअगरied ISDN controller
 * or (क्रम @contr == 0) the driver itself.
 * Return value: CAPI result code
 */

u16 capi20_get_serial(u32 contr, u8 serial[CAPI_SERIAL_LEN])
अणु
	काष्ठा capi_ctr *ctr;
	u16 ret;

	अगर (contr == 0) अणु
		strlcpy(serial, driver_serial, CAPI_SERIAL_LEN);
		वापस CAPI_NOERROR;
	पूर्ण

	mutex_lock(&capi_controller_lock);

	ctr = get_capi_ctr_by_nr(contr);
	अगर (ctr && ctr->state == CAPI_CTR_RUNNING) अणु
		strlcpy(serial, ctr->serial, CAPI_SERIAL_LEN);
		ret = CAPI_NOERROR;
	पूर्ण अन्यथा
		ret = CAPI_REGNOTINSTALLED;

	mutex_unlock(&capi_controller_lock);
	वापस ret;
पूर्ण

/**
 * capi20_get_profile() - CAPI 2.0 operation CAPI_GET_PROखाता
 * @contr:	controller number.
 * @profp:	result काष्ठाure.
 *
 * Retrieve capability inक्रमmation क्रम the specअगरied ISDN controller
 * or (क्रम @contr == 0) the number of installed controllers.
 * Return value: CAPI result code
 */

u16 capi20_get_profile(u32 contr, काष्ठा capi_profile *profp)
अणु
	काष्ठा capi_ctr *ctr;
	u16 ret;

	अगर (contr == 0) अणु
		profp->ncontroller = ncontrollers;
		वापस CAPI_NOERROR;
	पूर्ण

	mutex_lock(&capi_controller_lock);

	ctr = get_capi_ctr_by_nr(contr);
	अगर (ctr && ctr->state == CAPI_CTR_RUNNING) अणु
		स_नकल(profp, &ctr->profile, माप(काष्ठा capi_profile));
		ret = CAPI_NOERROR;
	पूर्ण अन्यथा
		ret = CAPI_REGNOTINSTALLED;

	mutex_unlock(&capi_controller_lock);
	वापस ret;
पूर्ण

/**
 * capi20_manufacturer() - CAPI 2.0 operation CAPI_MANUFACTURER
 * @cmd:	command.
 * @data:	parameter.
 *
 * Perक्रमm manufacturer specअगरic command.
 * Return value: CAPI result code
 */

पूर्णांक capi20_manufacturer(अचिन्हित दीर्घ cmd, व्योम __user *data)
अणु
	काष्ठा capi_ctr *ctr;
	पूर्णांक retval;

	चयन (cmd) अणु
	हाल KCAPI_CMD_TRACE:
	अणु
		kcapi_flagdef fdef;

		अगर (copy_from_user(&fdef, data, माप(kcapi_flagdef)))
			वापस -EFAULT;

		mutex_lock(&capi_controller_lock);

		ctr = get_capi_ctr_by_nr(fdef.contr);
		अगर (ctr) अणु
			ctr->traceflag = fdef.flag;
			prपूर्णांकk(KERN_INFO "kcapi: contr [%03d] set trace=%d\n",
			       ctr->cnr, ctr->traceflag);
			retval = 0;
		पूर्ण अन्यथा
			retval = -ESRCH;

		mutex_unlock(&capi_controller_lock);

		वापस retval;
	पूर्ण

	शेष:
		prपूर्णांकk(KERN_ERR "kcapi: manufacturer command %lu unknown.\n",
		       cmd);
		अवरोध;

	पूर्ण
	वापस -EINVAL;
पूर्ण

/* ------------------------------------------------------------- */
/* -------- Init & Cleanup ------------------------------------- */
/* ------------------------------------------------------------- */

/*
 * init / निकास functions
 */

पूर्णांक __init kcapi_init(व्योम)
अणु
	पूर्णांक err;

	kcapi_wq = alloc_workqueue("kcapi", 0, 0);
	अगर (!kcapi_wq)
		वापस -ENOMEM;

	err = cdebug_init();
	अगर (err) अणु
		destroy_workqueue(kcapi_wq);
		वापस err;
	पूर्ण

	kcapi_proc_init();
	वापस 0;
पूर्ण

व्योम kcapi_निकास(व्योम)
अणु
	kcapi_proc_निकास();

	cdebug_निकास();
	destroy_workqueue(kcapi_wq);
पूर्ण
