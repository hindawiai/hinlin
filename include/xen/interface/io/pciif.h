<शैली गुरु>
/*
 * PCI Backend/Frontend Common Data Structures & Macros
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 *   Author: Ryan Wilson <hap9@epoch.ncsc.mil>
 */
#अगर_अघोषित __XEN_PCI_COMMON_H__
#घोषणा __XEN_PCI_COMMON_H__

/* Be sure to bump this number अगर you change this file */
#घोषणा XEN_PCI_MAGIC "7"

/* xen_pci_sharedinfo flags */
#घोषणा	_XEN_PCIF_active		(0)
#घोषणा	XEN_PCIF_active			(1<<_XEN_PCIF_active)
#घोषणा	_XEN_PCIB_AERHANDLER		(1)
#घोषणा	XEN_PCIB_AERHANDLER		(1<<_XEN_PCIB_AERHANDLER)
#घोषणा	_XEN_PCIB_active		(2)
#घोषणा	XEN_PCIB_active			(1<<_XEN_PCIB_active)

/* xen_pci_op commands */
#घोषणा	XEN_PCI_OP_conf_पढ़ो		(0)
#घोषणा	XEN_PCI_OP_conf_ग_लिखो		(1)
#घोषणा	XEN_PCI_OP_enable_msi		(2)
#घोषणा	XEN_PCI_OP_disable_msi		(3)
#घोषणा	XEN_PCI_OP_enable_msix		(4)
#घोषणा	XEN_PCI_OP_disable_msix		(5)
#घोषणा	XEN_PCI_OP_aer_detected		(6)
#घोषणा	XEN_PCI_OP_aer_resume		(7)
#घोषणा	XEN_PCI_OP_aer_mmio		(8)
#घोषणा	XEN_PCI_OP_aer_slotreset	(9)

/* xen_pci_op error numbers */
#घोषणा	XEN_PCI_ERR_success		(0)
#घोषणा	XEN_PCI_ERR_dev_not_found	(-1)
#घोषणा	XEN_PCI_ERR_invalid_offset	(-2)
#घोषणा	XEN_PCI_ERR_access_denied	(-3)
#घोषणा	XEN_PCI_ERR_not_implemented	(-4)
/* XEN_PCI_ERR_op_failed - backend failed to complete the operation */
#घोषणा XEN_PCI_ERR_op_failed		(-5)

/*
 * it should be PAGE_SIZE-माप(काष्ठा xen_pci_op))/माप(काष्ठा msix_entry))
 * Should not exceed 128
 */
#घोषणा SH_INFO_MAX_VEC			128

काष्ठा xen_msix_entry अणु
	uपूर्णांक16_t vector;
	uपूर्णांक16_t entry;
पूर्ण;
काष्ठा xen_pci_op अणु
	/* IN: what action to perक्रमm: XEN_PCI_OP_* */
	uपूर्णांक32_t cmd;

	/* OUT: will contain an error number (अगर any) from त्रुटिसं.स */
	पूर्णांक32_t err;

	/* IN: which device to touch */
	uपूर्णांक32_t करोमुख्य; /* PCI Doमुख्य/Segment */
	uपूर्णांक32_t bus;
	uपूर्णांक32_t devfn;

	/* IN: which configuration रेजिस्टरs to touch */
	पूर्णांक32_t offset;
	पूर्णांक32_t size;

	/* IN/OUT: Contains the result after a READ or the value to WRITE */
	uपूर्णांक32_t value;
	/* IN: Contains extra inक्रम क्रम this operation */
	uपूर्णांक32_t info;
	/*IN:  param क्रम msi-x */
	काष्ठा xen_msix_entry msix_entries[SH_INFO_MAX_VEC];
पूर्ण;

/*used क्रम pcie aer handling*/
काष्ठा xen_pcie_aer_op अणु
	/* IN: what action to perक्रमm: XEN_PCI_OP_* */
	uपूर्णांक32_t cmd;
	/*IN/OUT: वापस aer_op result or carry error_detected state as input*/
	पूर्णांक32_t err;

	/* IN: which device to touch */
	uपूर्णांक32_t करोमुख्य; /* PCI Doमुख्य/Segment*/
	uपूर्णांक32_t bus;
	uपूर्णांक32_t devfn;
पूर्ण;
काष्ठा xen_pci_sharedinfo अणु
	/* flags - XEN_PCIF_* */
	uपूर्णांक32_t flags;
	काष्ठा xen_pci_op op;
	काष्ठा xen_pcie_aer_op aer_op;
पूर्ण;

#पूर्ण_अगर /* __XEN_PCI_COMMON_H__ */
