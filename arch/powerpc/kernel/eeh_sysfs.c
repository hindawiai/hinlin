<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Sysfs entries क्रम PCI Error Recovery क्रम PAPR-compliant platक्रमm.
 * Copyright IBM Corporation 2007
 * Copyright Linas Vepstas <linas@austin.ibm.com> 2007
 *
 * Send comments and feedback to Linas Vepstas <linas@austin.ibm.com>
 */
#समावेश <linux/pci.h>
#समावेश <linux/स्थिति.स>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/pci-bridge.h>

/**
 * EEH_SHOW_ATTR -- Create sysfs entry क्रम eeh statistic
 * @_name: name of file in sysfs directory
 * @_memb: name of member in काष्ठा eeh_dev to access
 * @_क्रमmat: म_लिखो क्रमmat क्रम display
 *
 * All of the attributes look very similar, so just
 * स्वतः-gen a cut-n-paste routine to display them.
 */
#घोषणा EEH_SHOW_ATTR(_name,_memb,_क्रमmat)               \
अटल sमाप_प्रकार eeh_show_##_name(काष्ठा device *dev,      \
		काष्ठा device_attribute *attr, अक्षर *buf)          \
अणु                                                        \
	काष्ठा pci_dev *pdev = to_pci_dev(dev);               \
	काष्ठा eeh_dev *edev = pci_dev_to_eeh_dev(pdev);      \
	                                                      \
	अगर (!edev)                                            \
		वापस 0;                                     \
	                                                      \
	वापस प्र_लिखो(buf, _क्रमmat "\n", edev->_memb);       \
पूर्ण                                                        \
अटल DEVICE_ATTR(_name, 0444, eeh_show_##_name, शून्य);

EEH_SHOW_ATTR(eeh_mode,            mode,            "0x%x");
EEH_SHOW_ATTR(eeh_pe_config_addr,  pe_config_addr,  "0x%x");

अटल sमाप_प्रकार eeh_pe_state_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा eeh_dev *edev = pci_dev_to_eeh_dev(pdev);
	पूर्णांक state;

	अगर (!edev || !edev->pe)
		वापस -ENODEV;

	state = eeh_ops->get_state(edev->pe, शून्य);
	वापस प्र_लिखो(buf, "0x%08x 0x%08x\n",
		       state, edev->pe->state);
पूर्ण

अटल sमाप_प्रकार eeh_pe_state_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा eeh_dev *edev = pci_dev_to_eeh_dev(pdev);

	अगर (!edev || !edev->pe)
		वापस -ENODEV;

	/* Nothing to करो अगर it's not frozen */
	अगर (!(edev->pe->state & EEH_PE_ISOLATED))
		वापस count;

	अगर (eeh_unमुक्तze_pe(edev->pe))
		वापस -EIO;
	eeh_pe_state_clear(edev->pe, EEH_PE_ISOLATED, true);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(eeh_pe_state);

#अगर defined(CONFIG_PCI_IOV) && defined(CONFIG_PPC_PSERIES)
अटल sमाप_प्रकार eeh_notअगरy_resume_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा eeh_dev *edev = pci_dev_to_eeh_dev(pdev);
	काष्ठा pci_dn *pdn = pci_get_pdn(pdev);

	अगर (!edev || !edev->pe)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%d\n", pdn->last_allow_rc);
पूर्ण

अटल sमाप_प्रकार eeh_notअगरy_resume_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा eeh_dev *edev = pci_dev_to_eeh_dev(pdev);

	अगर (!edev || !edev->pe || !eeh_ops->notअगरy_resume)
		वापस -ENODEV;

	अगर (eeh_ops->notअगरy_resume(edev))
		वापस -EIO;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(eeh_notअगरy_resume);

अटल पूर्णांक eeh_notअगरy_resume_add(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device_node *np;
	पूर्णांक rc = 0;

	np = pci_device_to_OF_node(pdev->is_physfn ? pdev : pdev->physfn);

	अगर (of_property_पढ़ो_bool(np, "ibm,is-open-sriov-pf"))
		rc = device_create_file(&pdev->dev, &dev_attr_eeh_notअगरy_resume);

	वापस rc;
पूर्ण

अटल व्योम eeh_notअगरy_resume_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device_node *np;

	np = pci_device_to_OF_node(pdev->is_physfn ? pdev : pdev->physfn);

	अगर (of_property_पढ़ो_bool(np, "ibm,is-open-sriov-pf"))
		device_हटाओ_file(&pdev->dev, &dev_attr_eeh_notअगरy_resume);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक eeh_notअगरy_resume_add(काष्ठा pci_dev *pdev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम eeh_notअगरy_resume_हटाओ(काष्ठा pci_dev *pdev) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV && CONFIG PPC_PSERIES*/

व्योम eeh_sysfs_add_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा eeh_dev *edev = pci_dev_to_eeh_dev(pdev);
	पूर्णांक rc=0;

	अगर (!eeh_enabled())
		वापस;

	अगर (edev && (edev->mode & EEH_DEV_SYSFS))
		वापस;

	rc += device_create_file(&pdev->dev, &dev_attr_eeh_mode);
	rc += device_create_file(&pdev->dev, &dev_attr_eeh_pe_config_addr);
	rc += device_create_file(&pdev->dev, &dev_attr_eeh_pe_state);
	rc += eeh_notअगरy_resume_add(pdev);

	अगर (rc)
		pr_warn("EEH: Unable to create sysfs entries\n");
	अन्यथा अगर (edev)
		edev->mode |= EEH_DEV_SYSFS;
पूर्ण

व्योम eeh_sysfs_हटाओ_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा eeh_dev *edev = pci_dev_to_eeh_dev(pdev);

	अगर (!edev) अणु
		WARN_ON(eeh_enabled());
		वापस;
	पूर्ण

	edev->mode &= ~EEH_DEV_SYSFS;

	/*
	 * The parent directory might have been हटाओd. We needn't
	 * जारी क्रम that हाल.
	 */
	अगर (!pdev->dev.kobj.sd)
		वापस;

	device_हटाओ_file(&pdev->dev, &dev_attr_eeh_mode);
	device_हटाओ_file(&pdev->dev, &dev_attr_eeh_pe_config_addr);
	device_हटाओ_file(&pdev->dev, &dev_attr_eeh_pe_state);

	eeh_notअगरy_resume_हटाओ(pdev);
पूर्ण
