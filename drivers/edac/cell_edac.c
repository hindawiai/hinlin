<शैली गुरु>
/*
 * Cell MIC driver क्रम ECC counting
 *
 * Copyright 2007 Benjamin Herrenschmidt, IBM Corp.
 *                <benh@kernel.crashing.org>
 *
 * This file may be distributed under the terms of the
 * GNU General Public License.
 */
#अघोषित DEBUG

#समावेश <linux/edac.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/cell-regs.h>

#समावेश "edac_module.h"

काष्ठा cell_edac_priv
अणु
	काष्ठा cbe_mic_पंचांग_regs __iomem	*regs;
	पूर्णांक				node;
	पूर्णांक				chanmask;
#अगर_घोषित DEBUG
	u64				prev_fir;
#पूर्ण_अगर
पूर्ण;

अटल व्योम cell_edac_count_ce(काष्ठा mem_ctl_info *mci, पूर्णांक chan, u64 ar)
अणु
	काष्ठा cell_edac_priv		*priv = mci->pvt_info;
	काष्ठा csrow_info		*csrow = mci->csrows[0];
	अचिन्हित दीर्घ			address, pfn, offset, syndrome;

	dev_dbg(mci->pdev, "ECC CE err on node %d, channel %d, ar = 0x%016llx\n",
		priv->node, chan, ar);

	/* Address decoding is likely a bit bogus, to dbl check */
	address = (ar & 0xffffffffe0000000ul) >> 29;
	अगर (priv->chanmask == 0x3)
		address = (address << 1) | chan;
	pfn = address >> PAGE_SHIFT;
	offset = address & ~PAGE_MASK;
	syndrome = (ar & 0x000000001fe00000ul) >> 21;

	/* TODO: Decoding of the error address */
	edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
			     csrow->first_page + pfn, offset, syndrome,
			     0, chan, -1, "", "");
पूर्ण

अटल व्योम cell_edac_count_ue(काष्ठा mem_ctl_info *mci, पूर्णांक chan, u64 ar)
अणु
	काष्ठा cell_edac_priv		*priv = mci->pvt_info;
	काष्ठा csrow_info		*csrow = mci->csrows[0];
	अचिन्हित दीर्घ			address, pfn, offset;

	dev_dbg(mci->pdev, "ECC UE err on node %d, channel %d, ar = 0x%016llx\n",
		priv->node, chan, ar);

	/* Address decoding is likely a bit bogus, to dbl check */
	address = (ar & 0xffffffffe0000000ul) >> 29;
	अगर (priv->chanmask == 0x3)
		address = (address << 1) | chan;
	pfn = address >> PAGE_SHIFT;
	offset = address & ~PAGE_MASK;

	/* TODO: Decoding of the error address */
	edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
			     csrow->first_page + pfn, offset, 0,
			     0, chan, -1, "", "");
पूर्ण

अटल व्योम cell_edac_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा cell_edac_priv		*priv = mci->pvt_info;
	u64				fir, addreg, clear = 0;

	fir = in_be64(&priv->regs->mic_fir);
#अगर_घोषित DEBUG
	अगर (fir != priv->prev_fir) अणु
		dev_dbg(mci->pdev, "fir change : 0x%016lx\n", fir);
		priv->prev_fir = fir;
	पूर्ण
#पूर्ण_अगर
	अगर ((priv->chanmask & 0x1) && (fir & CBE_MIC_FIR_ECC_SINGLE_0_ERR)) अणु
		addreg = in_be64(&priv->regs->mic_df_ecc_address_0);
		clear |= CBE_MIC_FIR_ECC_SINGLE_0_RESET;
		cell_edac_count_ce(mci, 0, addreg);
	पूर्ण
	अगर ((priv->chanmask & 0x2) && (fir & CBE_MIC_FIR_ECC_SINGLE_1_ERR)) अणु
		addreg = in_be64(&priv->regs->mic_df_ecc_address_1);
		clear |= CBE_MIC_FIR_ECC_SINGLE_1_RESET;
		cell_edac_count_ce(mci, 1, addreg);
	पूर्ण
	अगर ((priv->chanmask & 0x1) && (fir & CBE_MIC_FIR_ECC_MULTI_0_ERR)) अणु
		addreg = in_be64(&priv->regs->mic_df_ecc_address_0);
		clear |= CBE_MIC_FIR_ECC_MULTI_0_RESET;
		cell_edac_count_ue(mci, 0, addreg);
	पूर्ण
	अगर ((priv->chanmask & 0x2) && (fir & CBE_MIC_FIR_ECC_MULTI_1_ERR)) अणु
		addreg = in_be64(&priv->regs->mic_df_ecc_address_1);
		clear |= CBE_MIC_FIR_ECC_MULTI_1_RESET;
		cell_edac_count_ue(mci, 1, addreg);
	पूर्ण

	/* The procedure क्रम clearing FIR bits is a bit ... weird */
	अगर (clear) अणु
		fir &= ~(CBE_MIC_FIR_ECC_ERR_MASK | CBE_MIC_FIR_ECC_SET_MASK);
		fir |= CBE_MIC_FIR_ECC_RESET_MASK;
		fir &= ~clear;
		out_be64(&priv->regs->mic_fir, fir);
		(व्योम)in_be64(&priv->regs->mic_fir);

		mb();	/* sync up */
#अगर_घोषित DEBUG
		fir = in_be64(&priv->regs->mic_fir);
		dev_dbg(mci->pdev, "fir clear  : 0x%016lx\n", fir);
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम cell_edac_init_csrows(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा csrow_info		*csrow = mci->csrows[0];
	काष्ठा dimm_info		*dimm;
	काष्ठा cell_edac_priv		*priv = mci->pvt_info;
	काष्ठा device_node		*np;
	पूर्णांक				j;
	u32				nr_pages;

	क्रम_each_node_by_name(np, "memory") अणु
		काष्ठा resource r;

		/* We "know" that the Cell firmware only creates one entry
		 * in the "memory" nodes. If that changes, this code will
		 * need to be adapted.
		 */
		अगर (of_address_to_resource(np, 0, &r))
			जारी;
		अगर (of_node_to_nid(np) != priv->node)
			जारी;
		csrow->first_page = r.start >> PAGE_SHIFT;
		nr_pages = resource_size(&r) >> PAGE_SHIFT;
		csrow->last_page = csrow->first_page + nr_pages - 1;

		क्रम (j = 0; j < csrow->nr_channels; j++) अणु
			dimm = csrow->channels[j]->dimm;
			dimm->mtype = MEM_XDR;
			dimm->edac_mode = EDAC_SECDED;
			dimm->nr_pages = nr_pages / csrow->nr_channels;
		पूर्ण
		dev_dbg(mci->pdev,
			"Initialized on node %d, chanmask=0x%x,"
			" first_page=0x%lx, nr_pages=0x%x\n",
			priv->node, priv->chanmask,
			csrow->first_page, nr_pages);
		अवरोध;
	पूर्ण
	of_node_put(np);
पूर्ण

अटल पूर्णांक cell_edac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cbe_mic_पंचांग_regs __iomem	*regs;
	काष्ठा mem_ctl_info		*mci;
	काष्ठा edac_mc_layer		layers[2];
	काष्ठा cell_edac_priv		*priv;
	u64				reg;
	पूर्णांक				rc, chanmask, num_chans;

	regs = cbe_get_cpu_mic_पंचांग_regs(cbe_node_to_cpu(pdev->id));
	अगर (regs == शून्य)
		वापस -ENODEV;

	edac_op_state = EDAC_OPSTATE_POLL;

	/* Get channel population */
	reg = in_be64(&regs->mic_mnt_cfg);
	dev_dbg(&pdev->dev, "MIC_MNT_CFG = 0x%016llx\n", reg);
	chanmask = 0;
	अगर (reg & CBE_MIC_MNT_CFG_CHAN_0_POP)
		chanmask |= 0x1;
	अगर (reg & CBE_MIC_MNT_CFG_CHAN_1_POP)
		chanmask |= 0x2;
	अगर (chanmask == 0) अणु
		dev_warn(&pdev->dev,
			 "Yuck ! No channel populated ? Aborting !\n");
		वापस -ENODEV;
	पूर्ण
	dev_dbg(&pdev->dev, "Initial FIR = 0x%016llx\n",
		in_be64(&regs->mic_fir));

	/* Allocate & init EDAC MC data काष्ठाure */
	num_chans = chanmask == 3 ? 2 : 1;

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = 1;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = num_chans;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(pdev->id, ARRAY_SIZE(layers), layers,
			    माप(काष्ठा cell_edac_priv));
	अगर (mci == शून्य)
		वापस -ENOMEM;
	priv = mci->pvt_info;
	priv->regs = regs;
	priv->node = pdev->id;
	priv->chanmask = chanmask;
	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FLAG_XDR;
	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_EC | EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_EC | EDAC_FLAG_SECDED;
	mci->mod_name = "cell_edac";
	mci->ctl_name = "MIC";
	mci->dev_name = dev_name(&pdev->dev);
	mci->edac_check = cell_edac_check;
	cell_edac_init_csrows(mci);

	/* Register with EDAC core */
	rc = edac_mc_add_mc(mci);
	अगर (rc) अणु
		dev_err(&pdev->dev, "failed to register with EDAC core\n");
		edac_mc_मुक्त(mci);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cell_edac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mem_ctl_info *mci = edac_mc_del_mc(&pdev->dev);
	अगर (mci)
		edac_mc_मुक्त(mci);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cell_edac_driver = अणु
	.driver		= अणु
		.name	= "cbe-mic",
	पूर्ण,
	.probe		= cell_edac_probe,
	.हटाओ		= cell_edac_हटाओ,
पूर्ण;

अटल पूर्णांक __init cell_edac_init(व्योम)
अणु
	/* Sanity check रेजिस्टरs data काष्ठाure */
	BUILD_BUG_ON(दुरत्व(काष्ठा cbe_mic_पंचांग_regs,
			      mic_df_ecc_address_0) != 0xf8);
	BUILD_BUG_ON(दुरत्व(काष्ठा cbe_mic_पंचांग_regs,
			      mic_df_ecc_address_1) != 0x1b8);
	BUILD_BUG_ON(दुरत्व(काष्ठा cbe_mic_पंचांग_regs,
			      mic_df_config) != 0x218);
	BUILD_BUG_ON(दुरत्व(काष्ठा cbe_mic_पंचांग_regs,
			      mic_fir) != 0x230);
	BUILD_BUG_ON(दुरत्व(काष्ठा cbe_mic_पंचांग_regs,
			      mic_mnt_cfg) != 0x210);
	BUILD_BUG_ON(दुरत्व(काष्ठा cbe_mic_पंचांग_regs,
			      mic_exc) != 0x208);

	वापस platक्रमm_driver_रेजिस्टर(&cell_edac_driver);
पूर्ण

अटल व्योम __निकास cell_edac_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&cell_edac_driver);
पूर्ण

module_init(cell_edac_init);
module_निकास(cell_edac_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("ECC counting for Cell MIC");
