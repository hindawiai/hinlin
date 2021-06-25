<शैली गुरु>
/*
 * Copyright (c) 2016 Hisilicon Limited.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश "hns_roce_device.h"

अटल पूर्णांक hns_roce_pd_alloc(काष्ठा hns_roce_dev *hr_dev, अचिन्हित दीर्घ *pdn)
अणु
	वापस hns_roce_biपंचांगap_alloc(&hr_dev->pd_biपंचांगap, pdn) ? -ENOMEM : 0;
पूर्ण

अटल व्योम hns_roce_pd_मुक्त(काष्ठा hns_roce_dev *hr_dev, अचिन्हित दीर्घ pdn)
अणु
	hns_roce_biपंचांगap_मुक्त(&hr_dev->pd_biपंचांगap, pdn, BITMAP_NO_RR);
पूर्ण

पूर्णांक hns_roce_init_pd_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	वापस hns_roce_biपंचांगap_init(&hr_dev->pd_biपंचांगap, hr_dev->caps.num_pds,
				    hr_dev->caps.num_pds - 1,
				    hr_dev->caps.reserved_pds, 0);
पूर्ण

व्योम hns_roce_cleanup_pd_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	hns_roce_biपंचांगap_cleanup(&hr_dev->pd_biपंचांगap);
पूर्ण

पूर्णांक hns_roce_alloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ib_dev = ibpd->device;
	काष्ठा hns_roce_pd *pd = to_hr_pd(ibpd);
	पूर्णांक ret;

	ret = hns_roce_pd_alloc(to_hr_dev(ib_dev), &pd->pdn);
	अगर (ret) अणु
		ibdev_err(ib_dev, "failed to alloc pd, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	अगर (udata) अणु
		काष्ठा hns_roce_ib_alloc_pd_resp resp = अणु.pdn = pd->pdnपूर्ण;

		ret = ib_copy_to_udata(udata, &resp,
				       min(udata->outlen, माप(resp)));
		अगर (ret) अणु
			hns_roce_pd_मुक्त(to_hr_dev(ib_dev), pd->pdn);
			ibdev_err(ib_dev, "failed to copy to udata, ret = %d\n", ret);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक hns_roce_dealloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata)
अणु
	hns_roce_pd_मुक्त(to_hr_dev(pd->device), to_hr_pd(pd)->pdn);
	वापस 0;
पूर्ण

पूर्णांक hns_roce_uar_alloc(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_uar *uar)
अणु
	काष्ठा resource *res;
	पूर्णांक ret;

	/* Using biपंचांगap to manager UAR index */
	ret = hns_roce_biपंचांगap_alloc(&hr_dev->uar_table.biपंचांगap, &uar->logic_idx);
	अगर (ret)
		वापस -ENOMEM;

	अगर (uar->logic_idx > 0 && hr_dev->caps.phy_num_uars > 1)
		uar->index = (uar->logic_idx - 1) %
			     (hr_dev->caps.phy_num_uars - 1) + 1;
	अन्यथा
		uar->index = 0;

	अगर (!dev_is_pci(hr_dev->dev)) अणु
		res = platक्रमm_get_resource(hr_dev->pdev, IORESOURCE_MEM, 0);
		अगर (!res) अणु
			dev_err(&hr_dev->pdev->dev, "memory resource not found!\n");
			वापस -EINVAL;
		पूर्ण
		uar->pfn = ((res->start) >> PAGE_SHIFT) + uar->index;
	पूर्ण अन्यथा अणु
		uar->pfn = ((pci_resource_start(hr_dev->pci_dev, 2))
			   >> PAGE_SHIFT);
	पूर्ण

	वापस 0;
पूर्ण

व्योम hns_roce_uar_मुक्त(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_uar *uar)
अणु
	hns_roce_biपंचांगap_मुक्त(&hr_dev->uar_table.biपंचांगap, uar->logic_idx,
			     BITMAP_NO_RR);
पूर्ण

पूर्णांक hns_roce_init_uar_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	वापस hns_roce_biपंचांगap_init(&hr_dev->uar_table.biपंचांगap,
				    hr_dev->caps.num_uars,
				    hr_dev->caps.num_uars - 1,
				    hr_dev->caps.reserved_uars, 0);
पूर्ण

व्योम hns_roce_cleanup_uar_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	hns_roce_biपंचांगap_cleanup(&hr_dev->uar_table.biपंचांगap);
पूर्ण

अटल पूर्णांक hns_roce_xrcd_alloc(काष्ठा hns_roce_dev *hr_dev, u32 *xrcdn)
अणु
	अचिन्हित दीर्घ obj;
	पूर्णांक ret;

	ret = hns_roce_biपंचांगap_alloc(&hr_dev->xrcd_biपंचांगap, &obj);
	अगर (ret)
		वापस ret;

	*xrcdn = obj;

	वापस 0;
पूर्ण

अटल व्योम hns_roce_xrcd_मुक्त(काष्ठा hns_roce_dev *hr_dev,
			       u32 xrcdn)
अणु
	hns_roce_biपंचांगap_मुक्त(&hr_dev->xrcd_biपंचांगap, xrcdn, BITMAP_NO_RR);
पूर्ण

पूर्णांक hns_roce_init_xrcd_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	वापस hns_roce_biपंचांगap_init(&hr_dev->xrcd_biपंचांगap,
				    hr_dev->caps.num_xrcds,
				    hr_dev->caps.num_xrcds - 1,
				    hr_dev->caps.reserved_xrcds, 0);
पूर्ण

व्योम hns_roce_cleanup_xrcd_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	hns_roce_biपंचांगap_cleanup(&hr_dev->xrcd_biपंचांगap);
पूर्ण

पूर्णांक hns_roce_alloc_xrcd(काष्ठा ib_xrcd *ib_xrcd, काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ib_xrcd->device);
	काष्ठा hns_roce_xrcd *xrcd = to_hr_xrcd(ib_xrcd);
	पूर्णांक ret;

	अगर (!(hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_XRC))
		वापस -EINVAL;

	ret = hns_roce_xrcd_alloc(hr_dev, &xrcd->xrcdn);
	अगर (ret) अणु
		dev_err(hr_dev->dev, "failed to alloc xrcdn, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hns_roce_dealloc_xrcd(काष्ठा ib_xrcd *ib_xrcd, काष्ठा ib_udata *udata)
अणु
	hns_roce_xrcd_मुक्त(to_hr_dev(ib_xrcd->device),
			   to_hr_xrcd(ib_xrcd)->xrcdn);

	वापस 0;
पूर्ण
