<शैली गुरु>
/******************************************************************************
 * elfnote.h
 *
 * Definitions used क्रम the Xen ELF notes.
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
 * Copyright (c) 2006, Ian Campbell, XenSource Ltd.
 */

#अगर_अघोषित __XEN_PUBLIC_ELFNOTE_H__
#घोषणा __XEN_PUBLIC_ELFNOTE_H__

/*
 * The notes should live in a SHT_NOTE segment and have "Xen" in the
 * name field.
 *
 * Numeric types are either 4 or 8 bytes depending on the content of
 * the desc field.
 *
 * LEGACY indicated the fields in the legacy __xen_guest string which
 * this a note type replaces.
 *
 * String values (क्रम non-legacy) are शून्य terminated ASCII, also known
 * as ASCIZ type.
 */

/*
 * NAME=VALUE pair (string).
 */
#घोषणा XEN_ELFNOTE_INFO           0

/*
 * The भव address of the entry poपूर्णांक (numeric).
 *
 * LEGACY: VIRT_ENTRY
 */
#घोषणा XEN_ELFNOTE_ENTRY          1

/* The भव address of the hypercall transfer page (numeric).
 *
 * LEGACY: HYPERCALL_PAGE. (n.b. legacy value is a physical page
 * number not a भव address)
 */
#घोषणा XEN_ELFNOTE_HYPERCALL_PAGE 2

/* The भव address where the kernel image should be mapped (numeric).
 *
 * Defaults to 0.
 *
 * LEGACY: VIRT_BASE
 */
#घोषणा XEN_ELFNOTE_VIRT_BASE      3

/*
 * The offset of the ELF paddr field from the acutal required
 * pseuकरो-physical address (numeric).
 *
 * This is used to मुख्यtain backwards compatibility with older kernels
 * which wrote __PAGE_OFFSET पूर्णांकo that field. This field शेषs to 0
 * अगर not present.
 *
 * LEGACY: ELF_PADDR_OFFSET. (n.b. legacy शेष is VIRT_BASE)
 */
#घोषणा XEN_ELFNOTE_PADDR_OFFSET   4

/*
 * The version of Xen that we work with (string).
 *
 * LEGACY: XEN_VER
 */
#घोषणा XEN_ELFNOTE_XEN_VERSION    5

/*
 * The name of the guest operating प्रणाली (string).
 *
 * LEGACY: GUEST_OS
 */
#घोषणा XEN_ELFNOTE_GUEST_OS       6

/*
 * The version of the guest operating प्रणाली (string).
 *
 * LEGACY: GUEST_VER
 */
#घोषणा XEN_ELFNOTE_GUEST_VERSION  7

/*
 * The loader type (string).
 *
 * LEGACY: LOADER
 */
#घोषणा XEN_ELFNOTE_LOADER         8

/*
 * The kernel supports PAE (x86/32 only, string = "yes" or "no").
 *
 * LEGACY: PAE (n.b. The legacy पूर्णांकerface included a provision to
 * indicate 'extended-cr3' support allowing L3 page tables to be
 * placed above 4G. It is assumed that any kernel new enough to use
 * these ELF notes will include this and thereक्रमe "yes" here is
 * equivalent to "yes[entended-cr3]" in the __xen_guest पूर्णांकerface.
 */
#घोषणा XEN_ELFNOTE_PAE_MODE       9

/*
 * The features supported/required by this kernel (string).
 *
 * The string must consist of a list of feature names (as given in
 * features.h, without the "XENFEAT_" prefix) separated by '|'
 * अक्षरacters. If a feature is required क्रम the kernel to function
 * then the feature name must be preceded by a '!' अक्षरacter.
 *
 * LEGACY: FEATURES
 */
#घोषणा XEN_ELFNOTE_FEATURES      10

/*
 * The kernel requires the symbol table to be loaded (string = "yes" or "no")
 * LEGACY: BSD_SYMTAB (n.b. The legacy treated the presence or असलence
 * of this string as a boolean flag rather than requiring "yes" or
 * "no".
 */
#घोषणा XEN_ELFNOTE_BSD_SYMTAB    11

/*
 * The lowest address the hypervisor hole can begin at (numeric).
 *
 * This must not be set higher than HYPERVISOR_VIRT_START. Its presence
 * also indicates to the hypervisor that the kernel can deal with the
 * hole starting at a higher address.
 */
#घोषणा XEN_ELFNOTE_HV_START_LOW  12

/*
 * List of maddr_t-sized mask/value pairs describing how to recognize
 * (non-present) L1 page table entries carrying valid MFNs (numeric).
 */
#घोषणा XEN_ELFNOTE_L1_MFN_VALID  13

/*
 * Whether or not the guest supports cooperative suspend cancellation.
 * This is a numeric value.
 *
 * Default is 0
 */
#घोषणा XEN_ELFNOTE_SUSPEND_CANCEL 14

/*
 * The (non-शेष) location the initial phys-to-machine map should be
 * placed at by the hypervisor (Dom0) or the tools (DomU).
 * The kernel must be prepared क्रम this mapping to be established using
 * large pages, despite such otherwise not being available to guests.
 * The kernel must also be able to handle the page table pages used क्रम
 * this mapping not being accessible through the initial mapping.
 * (Only x86-64 supports this at present.)
 */
#घोषणा XEN_ELFNOTE_INIT_P2M      15

/*
 * Whether or not the guest can deal with being passed an initrd not
 * mapped through its initial page tables.
 */
#घोषणा XEN_ELFNOTE_MOD_START_PFN 16

/*
 * The features supported by this kernel (numeric).
 *
 * Other than XEN_ELFNOTE_FEATURES on pre-4.2 Xen, this note allows a
 * kernel to specअगरy support क्रम features that older hypervisors करोn't
 * know about. The set of features 4.2 and newer hypervisors will
 * consider supported by the kernel is the combination of the sets
 * specअगरied through this and the string note.
 *
 * LEGACY: FEATURES
 */
#घोषणा XEN_ELFNOTE_SUPPORTED_FEATURES 17

/*
 * Physical entry poपूर्णांक पूर्णांकo the kernel.
 *
 * 32bit entry poपूर्णांक पूर्णांकo the kernel. When requested to launch the
 * guest kernel in a HVM container, Xen will use this entry poपूर्णांक to
 * launch the guest in 32bit रक्षित mode with paging disabled.
 * Ignored otherwise.
 */
#घोषणा XEN_ELFNOTE_PHYS32_ENTRY 18

/*
 * The number of the highest elfnote defined.
 */
#घोषणा XEN_ELFNOTE_MAX XEN_ELFNOTE_PHYS32_ENTRY

#पूर्ण_अगर /* __XEN_PUBLIC_ELFNOTE_H__ */
