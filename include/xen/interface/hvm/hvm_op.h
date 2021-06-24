<शैली गुरु>
/*
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
 */

#अगर_अघोषित __XEN_PUBLIC_HVM_HVM_OP_H__
#घोषणा __XEN_PUBLIC_HVM_HVM_OP_H__

#समावेश <xen/पूर्णांकerface/xen.h>

/* Get/set subcommands: the second argument of the hypercall is a
 * poपूर्णांकer to a xen_hvm_param काष्ठा. */
#घोषणा HVMOP_set_param           0
#घोषणा HVMOP_get_param           1
काष्ठा xen_hvm_param अणु
    करोmid_t  करोmid;    /* IN */
    uपूर्णांक32_t index;    /* IN */
    uपूर्णांक64_t value;    /* IN/OUT */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_hvm_param);

/* Hपूर्णांक from PV drivers क्रम pagetable deकाष्ठाion. */
#घोषणा HVMOP_pagetable_dying       9
काष्ठा xen_hvm_pagetable_dying अणु
    /* Doमुख्य with a pagetable about to be destroyed. */
    करोmid_t  करोmid;
    /* guest physical address of the toplevel pagetable dying */
    aligned_u64 gpa;
पूर्ण;
प्रकार काष्ठा xen_hvm_pagetable_dying xen_hvm_pagetable_dying_t;
DEFINE_GUEST_HANDLE_STRUCT(xen_hvm_pagetable_dying_t);
 
क्रमागत hvmmem_type_t अणु
    HVMMEM_ram_rw,             /* Normal पढ़ो/ग_लिखो guest RAM */
    HVMMEM_ram_ro,             /* Read-only; ग_लिखोs are discarded */
    HVMMEM_mmio_dm,            /* Reads and ग_लिखो go to the device model */
पूर्ण;

#घोषणा HVMOP_get_mem_type    15
/* Return hvmmem_type_t क्रम the specअगरied pfn. */
काष्ठा xen_hvm_get_mem_type अणु
    /* Doमुख्य to be queried. */
    करोmid_t करोmid;
    /* OUT variable. */
    uपूर्णांक16_t mem_type;
    uपूर्णांक16_t pad[2]; /* align next field on 8-byte boundary */
    /* IN variable. */
    uपूर्णांक64_t pfn;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_hvm_get_mem_type);

#पूर्ण_अगर /* __XEN_PUBLIC_HVM_HVM_OP_H__ */
