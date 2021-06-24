<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2007 by Alan Stern
 */

/* this file is part of ehci-hcd.c */


/* Display the ports dedicated to the companion controller */
अटल sमाप_प्रकार companion_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा ehci_hcd		*ehci;
	पूर्णांक			nports, index, n;
	पूर्णांक			count = PAGE_SIZE;
	अक्षर			*ptr = buf;

	ehci = hcd_to_ehci(dev_get_drvdata(dev));
	nports = HCS_N_PORTS(ehci->hcs_params);

	क्रम (index = 0; index < nports; ++index) अणु
		अगर (test_bit(index, &ehci->companion_ports)) अणु
			n = scnम_लिखो(ptr, count, "%d\n", index + 1);
			ptr += n;
			count -= n;
		पूर्ण
	पूर्ण
	वापस ptr - buf;
पूर्ण

/*
 * Dedicate or undedicate a port to the companion controller.
 * Syntax is "[-]portnum", where a leading '-' sign means
 * वापस control of the port to the EHCI controller.
 */
अटल sमाप_प्रकार companion_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ehci_hcd		*ehci;
	पूर्णांक			portnum, new_owner;

	ehci = hcd_to_ehci(dev_get_drvdata(dev));
	new_owner = PORT_OWNER;		/* Owned by companion */
	अगर (माला_पूछो(buf, "%d", &portnum) != 1)
		वापस -EINVAL;
	अगर (portnum < 0) अणु
		portnum = - portnum;
		new_owner = 0;		/* Owned by EHCI */
	पूर्ण
	अगर (portnum <= 0 || portnum > HCS_N_PORTS(ehci->hcs_params))
		वापस -ENOENT;
	portnum--;
	अगर (new_owner)
		set_bit(portnum, &ehci->companion_ports);
	अन्यथा
		clear_bit(portnum, &ehci->companion_ports);
	set_owner(ehci, portnum, new_owner);
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(companion);


/*
 * Display / Set uframe_periodic_max
 */
अटल sमाप_प्रकार uframe_periodic_max_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा ehci_hcd		*ehci;
	पूर्णांक			n;

	ehci = hcd_to_ehci(dev_get_drvdata(dev));
	n = scnम_लिखो(buf, PAGE_SIZE, "%d\n", ehci->uframe_periodic_max);
	वापस n;
पूर्ण


अटल sमाप_प्रकार uframe_periodic_max_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ehci_hcd		*ehci;
	अचिन्हित		uframe_periodic_max;
	अचिन्हित		uframe;
	अचिन्हित दीर्घ		flags;
	sमाप_प्रकार			ret;

	ehci = hcd_to_ehci(dev_get_drvdata(dev));
	अगर (kstrtouपूर्णांक(buf, 0, &uframe_periodic_max) < 0)
		वापस -EINVAL;

	अगर (uframe_periodic_max < 100 || uframe_periodic_max >= 125) अणु
		ehci_info(ehci, "rejecting invalid request for "
				"uframe_periodic_max=%u\n", uframe_periodic_max);
		वापस -EINVAL;
	पूर्ण

	ret = -EINVAL;

	/*
	 * lock, so that our checking करोes not race with possible periodic
	 * bandwidth allocation through submitting new urbs.
	 */
	spin_lock_irqsave (&ehci->lock, flags);

	/*
	 * क्रम request to decrease max periodic bandwidth, we have to check
	 * to see whether the decrease is possible.
	 */
	अगर (uframe_periodic_max < ehci->uframe_periodic_max) अणु
		u8		allocated_max = 0;

		क्रम (uframe = 0; uframe < EHCI_BANDWIDTH_SIZE; ++uframe)
			allocated_max = max(allocated_max,
					ehci->bandwidth[uframe]);

		अगर (allocated_max > uframe_periodic_max) अणु
			ehci_info(ehci,
				"cannot decrease uframe_periodic_max because "
				"periodic bandwidth is already allocated "
				"(%u > %u)\n",
				allocated_max, uframe_periodic_max);
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	/* increasing is always ok */

	ehci_info(ehci, "setting max periodic bandwidth to %u%% "
			"(== %u usec/uframe)\n",
			100*uframe_periodic_max/125, uframe_periodic_max);

	अगर (uframe_periodic_max != 100)
		ehci_warn(ehci, "max periodic bandwidth set is non-standard\n");

	ehci->uframe_periodic_max = uframe_periodic_max;
	ret = count;

out_unlock:
	spin_unlock_irqrestore (&ehci->lock, flags);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RW(uframe_periodic_max);


अटल अंतरभूत पूर्णांक create_sysfs_files(काष्ठा ehci_hcd *ehci)
अणु
	काष्ठा device	*controller = ehci_to_hcd(ehci)->self.controller;
	पूर्णांक	i = 0;

	/* with पूर्णांकegrated TT there is no companion! */
	अगर (!ehci_is_TDI(ehci))
		i = device_create_file(controller, &dev_attr_companion);
	अगर (i)
		जाओ out;

	i = device_create_file(controller, &dev_attr_uframe_periodic_max);
out:
	वापस i;
पूर्ण

अटल अंतरभूत व्योम हटाओ_sysfs_files(काष्ठा ehci_hcd *ehci)
अणु
	काष्ठा device	*controller = ehci_to_hcd(ehci)->self.controller;

	/* with पूर्णांकegrated TT there is no companion! */
	अगर (!ehci_is_TDI(ehci))
		device_हटाओ_file(controller, &dev_attr_companion);

	device_हटाओ_file(controller, &dev_attr_uframe_periodic_max);
पूर्ण
