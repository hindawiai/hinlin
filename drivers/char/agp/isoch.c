<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Setup routines क्रम AGP 3.5 compliant bridges.
 */

#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "agp.h"

/* Generic AGP 3.5 enabling routines */

काष्ठा agp_3_5_dev अणु
	काष्ठा list_head list;
	u8 capndx;
	u32 maxbw;
	काष्ठा pci_dev *dev;
पूर्ण;

अटल व्योम agp_3_5_dev_list_insert(काष्ठा list_head *head, काष्ठा list_head *new)
अणु
	काष्ठा agp_3_5_dev *cur, *n = list_entry(new, काष्ठा agp_3_5_dev, list);
	काष्ठा list_head *pos;

	list_क्रम_each(pos, head) अणु
		cur = list_entry(pos, काष्ठा agp_3_5_dev, list);
		अगर (cur->maxbw > n->maxbw)
			अवरोध;
	पूर्ण
	list_add_tail(new, pos);
पूर्ण

अटल व्योम agp_3_5_dev_list_sort(काष्ठा agp_3_5_dev *list, अचिन्हित पूर्णांक ndevs)
अणु
	काष्ठा agp_3_5_dev *cur;
	काष्ठा pci_dev *dev;
	काष्ठा list_head *pos, *पंचांगp, *head = &list->list, *start = head->next;
	u32 nistat;

	INIT_LIST_HEAD(head);

	क्रम (pos=start; pos!=head; ) अणु
		cur = list_entry(pos, काष्ठा agp_3_5_dev, list);
		dev = cur->dev;

		pci_पढ़ो_config_dword(dev, cur->capndx+AGPNISTAT, &nistat);
		cur->maxbw = (nistat >> 16) & 0xff;

		पंचांगp = pos;
		pos = pos->next;
		agp_3_5_dev_list_insert(head, पंचांगp);
	पूर्ण
पूर्ण

/*
 * Initialize all isochronous transfer parameters क्रम an AGP 3.0
 * node (i.e. a host bridge in combination with the adapters
 * lying behind it...)
 */

अटल पूर्णांक agp_3_5_isochronous_node_enable(काष्ठा agp_bridge_data *bridge,
		काष्ठा agp_3_5_dev *dev_list, अचिन्हित पूर्णांक ndevs)
अणु
	/*
	 * Convenience काष्ठाure to make the calculations clearer
	 * here.  The field names come straight from the AGP 3.0 spec.
	 */
	काष्ठा isoch_data अणु
		u32 maxbw;
		u32 n;
		u32 y;
		u32 l;
		u32 rq;
		काष्ठा agp_3_5_dev *dev;
	पूर्ण;

	काष्ठा pci_dev *td = bridge->dev, *dev;
	काष्ठा list_head *head = &dev_list->list, *pos;
	काष्ठा agp_3_5_dev *cur;
	काष्ठा isoch_data *master, target;
	अचिन्हित पूर्णांक cdev = 0;
	u32 mnistat, tnistat, tstatus, mcmd;
	u16 tnicmd, mnicmd;
	u32 tot_bw = 0, tot_n = 0, tot_rq = 0, y_max, rq_isoch, rq_async;
	u32 step, rem, rem_isoch, rem_async;
	पूर्णांक ret = 0;

	/*
	 * We'll work with an array of isoch_data's (one क्रम each
	 * device in dev_list) throughout this function.
	 */
	master = kदो_स्मृति_array(ndevs, माप(*master), GFP_KERNEL);
	अगर (master == शून्य) अणु
		ret = -ENOMEM;
		जाओ get_out;
	पूर्ण

	/*
	 * Sort the device list by maxbw.  We need to करो this because the
	 * spec suggests that the devices with the smallest requirements
	 * have their resources allocated first, with all reमुख्यing resources
	 * falling to the device with the largest requirement.
	 *
	 * We करोn't exactly करो this, we भागide target resources by ndevs
	 * and split them amongst the AGP 3.0 devices.  The reमुख्यder of such
	 * भागision operations are dropped on the last device, sort of like
	 * the spec mentions it should be करोne.
	 *
	 * We can't करो this sort when we initially स्थिरruct the dev_list
	 * because we करोn't know until this function whether isochronous
	 * transfers are enabled and consequently whether maxbw will mean
	 * anything.
	 */
	agp_3_5_dev_list_sort(dev_list, ndevs);

	pci_पढ़ो_config_dword(td, bridge->capndx+AGPNISTAT, &tnistat);
	pci_पढ़ो_config_dword(td, bridge->capndx+AGPSTAT, &tstatus);

	/* Extract घातer-on शेषs from the target */
	target.maxbw = (tnistat >> 16) & 0xff;
	target.n     = (tnistat >> 8)  & 0xff;
	target.y     = (tnistat >> 6)  & 0x3;
	target.l     = (tnistat >> 3)  & 0x7;
	target.rq    = (tstatus >> 24) & 0xff;

	y_max = target.y;

	/*
	 * Extract घातer-on शेषs क्रम each device in dev_list.  Aदीर्घ
	 * the way, calculate the total isochronous bandwidth required
	 * by these devices and the largest requested payload size.
	 */
	list_क्रम_each(pos, head) अणु
		cur = list_entry(pos, काष्ठा agp_3_5_dev, list);
		dev = cur->dev;

		pci_पढ़ो_config_dword(dev, cur->capndx+AGPNISTAT, &mnistat);

		master[cdev].maxbw = (mnistat >> 16) & 0xff;
		master[cdev].n     = (mnistat >> 8)  & 0xff;
		master[cdev].y     = (mnistat >> 6)  & 0x3;
		master[cdev].dev   = cur;

		tot_bw += master[cdev].maxbw;
		y_max = max(y_max, master[cdev].y);

		cdev++;
	पूर्ण

	/* Check अगर this configuration has any chance of working */
	अगर (tot_bw > target.maxbw) अणु
		dev_err(&td->dev, "isochronous bandwidth required "
			"by AGP 3.0 devices exceeds that which is supported by "
			"the AGP 3.0 bridge!\n");
		ret = -ENODEV;
		जाओ मुक्त_and_निकास;
	पूर्ण

	target.y = y_max;

	/*
	 * Write the calculated payload size पूर्णांकo the target's NICMD
	 * रेजिस्टर.  Doing this directly effects the ISOCH_N value
	 * in the target's NISTAT रेजिस्टर, so we need to करो this now
	 * to get an accurate value क्रम ISOCH_N later.
	 */
	pci_पढ़ो_config_word(td, bridge->capndx+AGPNICMD, &tnicmd);
	tnicmd &= ~(0x3 << 6);
	tnicmd |= target.y << 6;
	pci_ग_लिखो_config_word(td, bridge->capndx+AGPNICMD, tnicmd);

	/* Reपढ़ो the target's ISOCH_N */
	pci_पढ़ो_config_dword(td, bridge->capndx+AGPNISTAT, &tnistat);
	target.n = (tnistat >> 8) & 0xff;

	/* Calculate the minimum ISOCH_N needed by each master */
	क्रम (cdev=0; cdev<ndevs; cdev++) अणु
		master[cdev].y = target.y;
		master[cdev].n = master[cdev].maxbw / (master[cdev].y + 1);

		tot_n += master[cdev].n;
	पूर्ण

	/* Exit अगर the minimal ISOCH_N allocation among the masters is more
	 * than the target can handle. */
	अगर (tot_n > target.n) अणु
		dev_err(&td->dev, "number of isochronous "
			"transactions per period required by AGP 3.0 devices "
			"exceeds that which is supported by the AGP 3.0 "
			"bridge!\n");
		ret = -ENODEV;
		जाओ मुक्त_and_निकास;
	पूर्ण

	/* Calculate left over ISOCH_N capability in the target.  We'll give
	 * this to the hungriest device (as per the spec) */
	rem  = target.n - tot_n;

	/*
	 * Calculate the minimum isochronous RQ depth needed by each master.
	 * Aदीर्घ the way, distribute the extra ISOCH_N capability calculated
	 * above.
	 */
	क्रम (cdev=0; cdev<ndevs; cdev++) अणु
		/*
		 * This is a little subtle.  If ISOCH_Y > 64B, then ISOCH_Y
		 * byte isochronous ग_लिखोs will be broken पूर्णांकo 64B pieces.
		 * This means we need to budget more RQ depth to account क्रम
		 * these kind of ग_लिखोs (each isochronous ग_लिखो is actually
		 * many ग_लिखोs on the AGP bus).
		 */
		master[cdev].rq = master[cdev].n;
		अगर (master[cdev].y > 0x1)
			master[cdev].rq *= (1 << (master[cdev].y - 1));

		tot_rq += master[cdev].rq;
	पूर्ण
	master[ndevs-1].n += rem;

	/* Figure the number of isochronous and asynchronous RQ slots the
	 * target is providing. */
	rq_isoch = (target.y > 0x1) ? target.n * (1 << (target.y - 1)) : target.n;
	rq_async = target.rq - rq_isoch;

	/* Exit अगर the minimal RQ needs of the masters exceeds what the target
	 * can provide. */
	अगर (tot_rq > rq_isoch) अणु
		dev_err(&td->dev, "number of request queue slots "
			"required by the isochronous bandwidth requested by "
			"AGP 3.0 devices exceeds the number provided by the "
			"AGP 3.0 bridge!\n");
		ret = -ENODEV;
		जाओ मुक्त_and_निकास;
	पूर्ण

	/* Calculate asynchronous RQ capability in the target (per master) as
	 * well as the total number of leftover isochronous RQ slots. */
	step      = rq_async / ndevs;
	rem_async = step + (rq_async % ndevs);
	rem_isoch = rq_isoch - tot_rq;

	/* Distribute the extra RQ slots calculated above and ग_लिखो our
	 * isochronous settings out to the actual devices. */
	क्रम (cdev=0; cdev<ndevs; cdev++) अणु
		cur = master[cdev].dev;
		dev = cur->dev;

		master[cdev].rq += (cdev == ndevs - 1)
		              ? (rem_async + rem_isoch) : step;

		pci_पढ़ो_config_word(dev, cur->capndx+AGPNICMD, &mnicmd);
		pci_पढ़ो_config_dword(dev, cur->capndx+AGPCMD, &mcmd);

		mnicmd &= ~(0xff << 8);
		mnicmd &= ~(0x3  << 6);
		mcmd   &= ~(0xff << 24);

		mnicmd |= master[cdev].n  << 8;
		mnicmd |= master[cdev].y  << 6;
		mcmd   |= master[cdev].rq << 24;

		pci_ग_लिखो_config_dword(dev, cur->capndx+AGPCMD, mcmd);
		pci_ग_लिखो_config_word(dev, cur->capndx+AGPNICMD, mnicmd);
	पूर्ण

मुक्त_and_निकास:
	kमुक्त(master);

get_out:
	वापस ret;
पूर्ण

/*
 * This function basically allocates request queue slots among the
 * AGP 3.0 प्रणालीs in nonisochronous nodes.  The algorithm is
 * pretty stupid, भागide the total number of RQ slots provided by the
 * target by ndevs.  Distribute this many slots to each AGP 3.0 device,
 * giving any left over slots to the last device in dev_list.
 */
अटल व्योम agp_3_5_nonisochronous_node_enable(काष्ठा agp_bridge_data *bridge,
		काष्ठा agp_3_5_dev *dev_list, अचिन्हित पूर्णांक ndevs)
अणु
	काष्ठा agp_3_5_dev *cur;
	काष्ठा list_head *head = &dev_list->list, *pos;
	u32 tstatus, mcmd;
	u32 trq, mrq, rem;
	अचिन्हित पूर्णांक cdev = 0;

	pci_पढ़ो_config_dword(bridge->dev, bridge->capndx+AGPSTAT, &tstatus);

	trq = (tstatus >> 24) & 0xff;
	mrq = trq / ndevs;

	rem = mrq + (trq % ndevs);

	क्रम (pos=head->next; cdev<ndevs; cdev++, pos=pos->next) अणु
		cur = list_entry(pos, काष्ठा agp_3_5_dev, list);

		pci_पढ़ो_config_dword(cur->dev, cur->capndx+AGPCMD, &mcmd);
		mcmd &= ~(0xff << 24);
		mcmd |= ((cdev == ndevs - 1) ? rem : mrq) << 24;
		pci_ग_लिखो_config_dword(cur->dev, cur->capndx+AGPCMD, mcmd);
	पूर्ण
पूर्ण

/*
 * Fully configure and enable an AGP 3.0 host bridge and all the devices
 * lying behind it.
 */
पूर्णांक agp_3_5_enable(काष्ठा agp_bridge_data *bridge)
अणु
	काष्ठा pci_dev *td = bridge->dev, *dev = शून्य;
	u8 mcapndx;
	u32 isoch;
	u32 tstatus, mstatus, ncapid;
	u32 mmajor;
	u16 mpstat;
	काष्ठा agp_3_5_dev *dev_list, *cur;
	काष्ठा list_head *head, *pos;
	अचिन्हित पूर्णांक ndevs = 0;
	पूर्णांक ret = 0;

	/* Extract some घातer-on शेषs from the target */
	pci_पढ़ो_config_dword(td, bridge->capndx+AGPSTAT, &tstatus);
	isoch     = (tstatus >> 17) & 0x1;
	अगर (isoch == 0)	/* isoch xfers not available, bail out. */
		वापस -ENODEV;

	/*
	 * Allocate a head क्रम our AGP 3.5 device list
	 * (multiple AGP v3 devices are allowed behind a single bridge).
	 */
	अगर ((dev_list = kदो_स्मृति(माप(*dev_list), GFP_KERNEL)) == शून्य) अणु
		ret = -ENOMEM;
		जाओ get_out;
	पूर्ण
	head = &dev_list->list;
	INIT_LIST_HEAD(head);

	/* Find all AGP devices, and add them to dev_list. */
	क्रम_each_pci_dev(dev) अणु
		mcapndx = pci_find_capability(dev, PCI_CAP_ID_AGP);
		अगर (mcapndx == 0)
			जारी;

		चयन ((dev->class >>8) & 0xff00) अणु
			हाल 0x0600:    /* Bridge */
				/* Skip bridges. We should call this function क्रम each one. */
				जारी;

			हाल 0x0001:    /* Unclassअगरied device */
				/* Don't know what this is, but log it क्रम investigation. */
				अगर (mcapndx != 0) अणु
					dev_info(&td->dev, "wacky, found unclassified AGP device %s [%04x/%04x]\n",
						 pci_name(dev),
						 dev->venकरोr, dev->device);
				पूर्ण
				जारी;

			हाल 0x0300:    /* Display controller */
			हाल 0x0400:    /* Mulसमयdia controller */
				अगर ((cur = kदो_स्मृति(माप(*cur), GFP_KERNEL)) == शून्य) अणु
					ret = -ENOMEM;
					जाओ मुक्त_and_निकास;
				पूर्ण
				cur->dev = dev;

				pos = &cur->list;
				list_add(pos, head);
				ndevs++;
				जारी;

			शेष:
				जारी;
		पूर्ण
	पूर्ण

	/*
	 * Take an initial pass through the devices lying behind our host
	 * bridge.  Make sure each one is actually an AGP 3.0 device, otherwise
	 * निकास with an error message.  Aदीर्घ the way store the AGP 3.0
	 * cap_ptr क्रम each device
	 */
	list_क्रम_each(pos, head) अणु
		cur = list_entry(pos, काष्ठा agp_3_5_dev, list);
		dev = cur->dev;

		pci_पढ़ो_config_word(dev, PCI_STATUS, &mpstat);
		अगर ((mpstat & PCI_STATUS_CAP_LIST) == 0)
			जारी;

		pci_पढ़ो_config_byte(dev, PCI_CAPABILITY_LIST, &mcapndx);
		अगर (mcapndx != 0) अणु
			करो अणु
				pci_पढ़ो_config_dword(dev, mcapndx, &ncapid);
				अगर ((ncapid & 0xff) != 2)
					mcapndx = (ncapid >> 8) & 0xff;
			पूर्ण
			जबतक (((ncapid & 0xff) != 2) && (mcapndx != 0));
		पूर्ण

		अगर (mcapndx == 0) अणु
			dev_err(&td->dev, "woah!  Non-AGP device %s on "
				"secondary bus of AGP 3.5 bridge!\n",
				pci_name(dev));
			ret = -ENODEV;
			जाओ मुक्त_and_निकास;
		पूर्ण

		mmajor = (ncapid >> AGP_MAJOR_VERSION_SHIFT) & 0xf;
		अगर (mmajor < 3) अणु
			dev_err(&td->dev, "woah!  AGP 2.0 device %s on "
				"secondary bus of AGP 3.5 bridge operating "
				"with AGP 3.0 electricals!\n", pci_name(dev));
			ret = -ENODEV;
			जाओ मुक्त_and_निकास;
		पूर्ण

		cur->capndx = mcapndx;

		pci_पढ़ो_config_dword(dev, cur->capndx+AGPSTAT, &mstatus);

		अगर (((mstatus >> 3) & 0x1) == 0) अणु
			dev_err(&td->dev, "woah!  AGP 3.x device %s not "
				"operating in AGP 3.x mode on secondary bus "
				"of AGP 3.5 bridge operating with AGP 3.0 "
				"electricals!\n", pci_name(dev));
			ret = -ENODEV;
			जाओ मुक्त_and_निकास;
		पूर्ण
	पूर्ण		

	/*
	 * Call functions to भागide target resources amongst the AGP 3.0
	 * masters.  This process is dramatically dअगरferent depending on
	 * whether isochronous transfers are supported.
	 */
	अगर (isoch) अणु
		ret = agp_3_5_isochronous_node_enable(bridge, dev_list, ndevs);
		अगर (ret) अणु
			dev_info(&td->dev, "something bad happened setting "
				 "up isochronous xfers; falling back to "
				 "non-isochronous xfer mode\n");
		पूर्ण अन्यथा अणु
			जाओ मुक्त_and_निकास;
		पूर्ण
	पूर्ण
	agp_3_5_nonisochronous_node_enable(bridge, dev_list, ndevs);

मुक्त_and_निकास:
	/* Be sure to मुक्त the dev_list */
	क्रम (pos=head->next; pos!=head; ) अणु
		cur = list_entry(pos, काष्ठा agp_3_5_dev, list);

		pos = pos->next;
		kमुक्त(cur);
	पूर्ण
	kमुक्त(dev_list);

get_out:
	वापस ret;
पूर्ण
