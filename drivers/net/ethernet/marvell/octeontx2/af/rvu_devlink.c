<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 RVU Devlink
 *
 * Copyright (C) 2020 Marvell.
 *
 */

#समावेश<linux/bitfield.h>

#समावेश "rvu.h"
#समावेश "rvu_reg.h"
#समावेश "rvu_struct.h"

#घोषणा DRV_NAME "octeontx2-af"

अटल पूर्णांक rvu_report_pair_start(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name)
अणु
	पूर्णांक err;

	err = devlink_fmsg_pair_nest_start(fmsg, name);
	अगर (err)
		वापस err;

	वापस  devlink_fmsg_obj_nest_start(fmsg);
पूर्ण

अटल पूर्णांक rvu_report_pair_end(काष्ठा devlink_fmsg *fmsg)
अणु
	पूर्णांक err;

	err = devlink_fmsg_obj_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस devlink_fmsg_pair_nest_end(fmsg);
पूर्ण

अटल bool rvu_common_request_irq(काष्ठा rvu *rvu, पूर्णांक offset,
				   स्थिर अक्षर *name, irq_handler_t fn)
अणु
	काष्ठा rvu_devlink *rvu_dl = rvu->rvu_dl;
	पूर्णांक rc;

	प्र_लिखो(&rvu->irq_name[offset * NAME_SIZE], name);
	rc = request_irq(pci_irq_vector(rvu->pdev, offset), fn, 0,
			 &rvu->irq_name[offset * NAME_SIZE], rvu_dl);
	अगर (rc)
		dev_warn(rvu->dev, "Failed to register %s irq\n", name);
	अन्यथा
		rvu->irq_allocated[offset] = true;

	वापस rvu->irq_allocated[offset];
पूर्ण

अटल व्योम rvu_nix_पूर्णांकr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rvu_nix_health_reporters *rvu_nix_health_reporter;

	rvu_nix_health_reporter = container_of(work, काष्ठा rvu_nix_health_reporters, पूर्णांकr_work);
	devlink_health_report(rvu_nix_health_reporter->rvu_hw_nix_पूर्णांकr_reporter,
			      "NIX_AF_RVU Error",
			      rvu_nix_health_reporter->nix_event_ctx);
पूर्ण

अटल irqवापस_t rvu_nix_af_rvu_पूर्णांकr_handler(पूर्णांक irq, व्योम *rvu_irq)
अणु
	काष्ठा rvu_nix_event_ctx *nix_event_context;
	काष्ठा rvu_devlink *rvu_dl = rvu_irq;
	काष्ठा rvu *rvu;
	पूर्णांक blkaddr;
	u64 पूर्णांकr;

	rvu = rvu_dl->rvu;
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, 0);
	अगर (blkaddr < 0)
		वापस IRQ_NONE;

	nix_event_context = rvu_dl->rvu_nix_health_reporter->nix_event_ctx;
	पूर्णांकr = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_RVU_INT);
	nix_event_context->nix_af_rvu_पूर्णांक = पूर्णांकr;

	/* Clear पूर्णांकerrupts */
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RVU_INT, पूर्णांकr);
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RVU_INT_ENA_W1C, ~0ULL);
	queue_work(rvu_dl->devlink_wq, &rvu_dl->rvu_nix_health_reporter->पूर्णांकr_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rvu_nix_gen_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rvu_nix_health_reporters *rvu_nix_health_reporter;

	rvu_nix_health_reporter = container_of(work, काष्ठा rvu_nix_health_reporters, gen_work);
	devlink_health_report(rvu_nix_health_reporter->rvu_hw_nix_gen_reporter,
			      "NIX_AF_GEN Error",
			      rvu_nix_health_reporter->nix_event_ctx);
पूर्ण

अटल irqवापस_t rvu_nix_af_rvu_gen_handler(पूर्णांक irq, व्योम *rvu_irq)
अणु
	काष्ठा rvu_nix_event_ctx *nix_event_context;
	काष्ठा rvu_devlink *rvu_dl = rvu_irq;
	काष्ठा rvu *rvu;
	पूर्णांक blkaddr;
	u64 पूर्णांकr;

	rvu = rvu_dl->rvu;
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, 0);
	अगर (blkaddr < 0)
		वापस IRQ_NONE;

	nix_event_context = rvu_dl->rvu_nix_health_reporter->nix_event_ctx;
	पूर्णांकr = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_GEN_INT);
	nix_event_context->nix_af_rvu_gen = पूर्णांकr;

	/* Clear पूर्णांकerrupts */
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_GEN_INT, पूर्णांकr);
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_GEN_INT_ENA_W1C, ~0ULL);
	queue_work(rvu_dl->devlink_wq, &rvu_dl->rvu_nix_health_reporter->gen_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rvu_nix_err_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rvu_nix_health_reporters *rvu_nix_health_reporter;

	rvu_nix_health_reporter = container_of(work, काष्ठा rvu_nix_health_reporters, err_work);
	devlink_health_report(rvu_nix_health_reporter->rvu_hw_nix_err_reporter,
			      "NIX_AF_ERR Error",
			      rvu_nix_health_reporter->nix_event_ctx);
पूर्ण

अटल irqवापस_t rvu_nix_af_rvu_err_handler(पूर्णांक irq, व्योम *rvu_irq)
अणु
	काष्ठा rvu_nix_event_ctx *nix_event_context;
	काष्ठा rvu_devlink *rvu_dl = rvu_irq;
	काष्ठा rvu *rvu;
	पूर्णांक blkaddr;
	u64 पूर्णांकr;

	rvu = rvu_dl->rvu;
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, 0);
	अगर (blkaddr < 0)
		वापस IRQ_NONE;

	nix_event_context = rvu_dl->rvu_nix_health_reporter->nix_event_ctx;
	पूर्णांकr = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_ERR_INT);
	nix_event_context->nix_af_rvu_err = पूर्णांकr;

	/* Clear पूर्णांकerrupts */
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_ERR_INT, पूर्णांकr);
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_ERR_INT_ENA_W1C, ~0ULL);
	queue_work(rvu_dl->devlink_wq, &rvu_dl->rvu_nix_health_reporter->err_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rvu_nix_ras_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rvu_nix_health_reporters *rvu_nix_health_reporter;

	rvu_nix_health_reporter = container_of(work, काष्ठा rvu_nix_health_reporters, ras_work);
	devlink_health_report(rvu_nix_health_reporter->rvu_hw_nix_ras_reporter,
			      "NIX_AF_RAS Error",
			      rvu_nix_health_reporter->nix_event_ctx);
पूर्ण

अटल irqवापस_t rvu_nix_af_rvu_ras_handler(पूर्णांक irq, व्योम *rvu_irq)
अणु
	काष्ठा rvu_nix_event_ctx *nix_event_context;
	काष्ठा rvu_devlink *rvu_dl = rvu_irq;
	काष्ठा rvu *rvu;
	पूर्णांक blkaddr;
	u64 पूर्णांकr;

	rvu = rvu_dl->rvu;
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, 0);
	अगर (blkaddr < 0)
		वापस IRQ_NONE;

	nix_event_context = rvu_dl->rvu_nix_health_reporter->nix_event_ctx;
	पूर्णांकr = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_ERR_INT);
	nix_event_context->nix_af_rvu_ras = पूर्णांकr;

	/* Clear पूर्णांकerrupts */
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RAS, पूर्णांकr);
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RAS_ENA_W1C, ~0ULL);
	queue_work(rvu_dl->devlink_wq, &rvu_dl->rvu_nix_health_reporter->ras_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rvu_nix_unरेजिस्टर_पूर्णांकerrupts(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_devlink *rvu_dl = rvu->rvu_dl;
	पूर्णांक offs, i, blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, 0);
	अगर (blkaddr < 0)
		वापस;

	offs = rvu_पढ़ो64(rvu, blkaddr, NIX_PRIV_AF_INT_CFG) & 0x3ff;
	अगर (!offs)
		वापस;

	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RVU_INT_ENA_W1C, ~0ULL);
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_GEN_INT_ENA_W1C, ~0ULL);
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_ERR_INT_ENA_W1C, ~0ULL);
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RAS_ENA_W1C, ~0ULL);

	अगर (rvu->irq_allocated[offs + NIX_AF_INT_VEC_RVU]) अणु
		मुक्त_irq(pci_irq_vector(rvu->pdev, offs + NIX_AF_INT_VEC_RVU),
			 rvu_dl);
		rvu->irq_allocated[offs + NIX_AF_INT_VEC_RVU] = false;
	पूर्ण

	क्रम (i = NIX_AF_INT_VEC_AF_ERR; i < NIX_AF_INT_VEC_CNT; i++)
		अगर (rvu->irq_allocated[offs + i]) अणु
			मुक्त_irq(pci_irq_vector(rvu->pdev, offs + i), rvu_dl);
			rvu->irq_allocated[offs + i] = false;
		पूर्ण
पूर्ण

अटल पूर्णांक rvu_nix_रेजिस्टर_पूर्णांकerrupts(काष्ठा rvu *rvu)
अणु
	पूर्णांक blkaddr, base;
	bool rc;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, 0);
	अगर (blkaddr < 0)
		वापस blkaddr;

	/* Get NIX AF MSIX vectors offset. */
	base = rvu_पढ़ो64(rvu, blkaddr, NIX_PRIV_AF_INT_CFG) & 0x3ff;
	अगर (!base) अणु
		dev_warn(rvu->dev,
			 "Failed to get NIX%d NIX_AF_INT vector offsets\n",
			 blkaddr - BLKADDR_NIX0);
		वापस 0;
	पूर्ण
	/* Register and enable NIX_AF_RVU_INT पूर्णांकerrupt */
	rc = rvu_common_request_irq(rvu, base +  NIX_AF_INT_VEC_RVU,
				    "NIX_AF_RVU_INT",
				    rvu_nix_af_rvu_पूर्णांकr_handler);
	अगर (!rc)
		जाओ err;
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RVU_INT_ENA_W1S, ~0ULL);

	/* Register and enable NIX_AF_GEN_INT पूर्णांकerrupt */
	rc = rvu_common_request_irq(rvu, base +  NIX_AF_INT_VEC_GEN,
				    "NIX_AF_GEN_INT",
				    rvu_nix_af_rvu_gen_handler);
	अगर (!rc)
		जाओ err;
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_GEN_INT_ENA_W1S, ~0ULL);

	/* Register and enable NIX_AF_ERR_INT पूर्णांकerrupt */
	rc = rvu_common_request_irq(rvu, base + NIX_AF_INT_VEC_AF_ERR,
				    "NIX_AF_ERR_INT",
				    rvu_nix_af_rvu_err_handler);
	अगर (!rc)
		जाओ err;
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_ERR_INT_ENA_W1S, ~0ULL);

	/* Register and enable NIX_AF_RAS पूर्णांकerrupt */
	rc = rvu_common_request_irq(rvu, base + NIX_AF_INT_VEC_POISON,
				    "NIX_AF_RAS",
				    rvu_nix_af_rvu_ras_handler);
	अगर (!rc)
		जाओ err;
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RAS_ENA_W1S, ~0ULL);

	वापस 0;
err:
	rvu_nix_unरेजिस्टर_पूर्णांकerrupts(rvu);
	वापस rc;
पूर्ण

अटल पूर्णांक rvu_nix_report_show(काष्ठा devlink_fmsg *fmsg, व्योम *ctx,
			       क्रमागत nix_af_rvu_health health_reporter)
अणु
	काष्ठा rvu_nix_event_ctx *nix_event_context;
	u64 पूर्णांकr_val;
	पूर्णांक err;

	nix_event_context = ctx;
	चयन (health_reporter) अणु
	हाल NIX_AF_RVU_INTR:
		पूर्णांकr_val = nix_event_context->nix_af_rvu_पूर्णांक;
		err = rvu_report_pair_start(fmsg, "NIX_AF_RVU");
		अगर (err)
			वापस err;
		err = devlink_fmsg_u64_pair_put(fmsg, "\tNIX RVU Interrupt Reg ",
						nix_event_context->nix_af_rvu_पूर्णांक);
		अगर (err)
			वापस err;
		अगर (पूर्णांकr_val & BIT_ULL(0)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tUnmap Slot Error");
			अगर (err)
				वापस err;
		पूर्ण
		err = rvu_report_pair_end(fmsg);
		अगर (err)
			वापस err;
		अवरोध;
	हाल NIX_AF_RVU_GEN:
		पूर्णांकr_val = nix_event_context->nix_af_rvu_gen;
		err = rvu_report_pair_start(fmsg, "NIX_AF_GENERAL");
		अगर (err)
			वापस err;
		err = devlink_fmsg_u64_pair_put(fmsg, "\tNIX General Interrupt Reg ",
						nix_event_context->nix_af_rvu_gen);
		अगर (err)
			वापस err;
		अगर (पूर्णांकr_val & BIT_ULL(0)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tRx multicast pkt drop");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(1)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tRx mirror pkt drop");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(4)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tSMQ flush done");
			अगर (err)
				वापस err;
		पूर्ण
		err = rvu_report_pair_end(fmsg);
		अगर (err)
			वापस err;
		अवरोध;
	हाल NIX_AF_RVU_ERR:
		पूर्णांकr_val = nix_event_context->nix_af_rvu_err;
		err = rvu_report_pair_start(fmsg, "NIX_AF_ERR");
		अगर (err)
			वापस err;
		err = devlink_fmsg_u64_pair_put(fmsg, "\tNIX Error Interrupt Reg ",
						nix_event_context->nix_af_rvu_err);
		अगर (err)
			वापस err;
		अगर (पूर्णांकr_val & BIT_ULL(14)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tFault on NIX_AQ_INST_S read");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(13)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tFault on NIX_AQ_RES_S write");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(12)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tAQ Doorbell Error");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(6)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tRx on unmapped PF_FUNC");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(5)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tRx multicast replication error");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(4)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tFault on NIX_RX_MCE_S read");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(3)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tFault on multicast WQE read");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(2)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tFault on mirror WQE read");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(1)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tFault on mirror pkt write");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(0)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tFault on multicast pkt write");
			अगर (err)
				वापस err;
		पूर्ण
		err = rvu_report_pair_end(fmsg);
		अगर (err)
			वापस err;
		अवरोध;
	हाल NIX_AF_RVU_RAS:
		पूर्णांकr_val = nix_event_context->nix_af_rvu_err;
		err = rvu_report_pair_start(fmsg, "NIX_AF_RAS");
		अगर (err)
			वापस err;
		err = devlink_fmsg_u64_pair_put(fmsg, "\tNIX RAS Interrupt Reg ",
						nix_event_context->nix_af_rvu_err);
		अगर (err)
			वापस err;
		err = devlink_fmsg_string_put(fmsg, "\n\tPoison Data on:");
		अगर (err)
			वापस err;
		अगर (पूर्णांकr_val & BIT_ULL(34)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tNIX_AQ_INST_S");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(33)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tNIX_AQ_RES_S");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(32)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tHW ctx");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(4)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tPacket from mirror buffer");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(3)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tPacket from multicast buffer");

			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(2)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tWQE read from mirror buffer");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(1)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tWQE read from multicast buffer");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (पूर्णांकr_val & BIT_ULL(0)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tNIX_RX_MCE_S read");
			अगर (err)
				वापस err;
		पूर्ण
		err = rvu_report_pair_end(fmsg);
		अगर (err)
			वापस err;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rvu_hw_nix_पूर्णांकr_dump(काष्ठा devlink_health_reporter *reporter,
				काष्ठा devlink_fmsg *fmsg, व्योम *ctx,
				काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_devlink *rvu_dl = rvu->rvu_dl;
	काष्ठा rvu_nix_event_ctx *nix_ctx;

	nix_ctx = rvu_dl->rvu_nix_health_reporter->nix_event_ctx;

	वापस ctx ? rvu_nix_report_show(fmsg, ctx, NIX_AF_RVU_INTR) :
		     rvu_nix_report_show(fmsg, nix_ctx, NIX_AF_RVU_INTR);
पूर्ण

अटल पूर्णांक rvu_hw_nix_पूर्णांकr_recover(काष्ठा devlink_health_reporter *reporter,
				   व्योम *ctx, काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_nix_event_ctx *nix_event_ctx = ctx;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, 0);
	अगर (blkaddr < 0)
		वापस blkaddr;

	अगर (nix_event_ctx->nix_af_rvu_पूर्णांक)
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RVU_INT_ENA_W1S, ~0ULL);

	वापस 0;
पूर्ण

अटल पूर्णांक rvu_hw_nix_gen_dump(काष्ठा devlink_health_reporter *reporter,
			       काष्ठा devlink_fmsg *fmsg, व्योम *ctx,
			       काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_devlink *rvu_dl = rvu->rvu_dl;
	काष्ठा rvu_nix_event_ctx *nix_ctx;

	nix_ctx = rvu_dl->rvu_nix_health_reporter->nix_event_ctx;

	वापस ctx ? rvu_nix_report_show(fmsg, ctx, NIX_AF_RVU_GEN) :
		     rvu_nix_report_show(fmsg, nix_ctx, NIX_AF_RVU_GEN);
पूर्ण

अटल पूर्णांक rvu_hw_nix_gen_recover(काष्ठा devlink_health_reporter *reporter,
				  व्योम *ctx, काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_nix_event_ctx *nix_event_ctx = ctx;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, 0);
	अगर (blkaddr < 0)
		वापस blkaddr;

	अगर (nix_event_ctx->nix_af_rvu_gen)
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_GEN_INT_ENA_W1S, ~0ULL);

	वापस 0;
पूर्ण

अटल पूर्णांक rvu_hw_nix_err_dump(काष्ठा devlink_health_reporter *reporter,
			       काष्ठा devlink_fmsg *fmsg, व्योम *ctx,
			       काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_devlink *rvu_dl = rvu->rvu_dl;
	काष्ठा rvu_nix_event_ctx *nix_ctx;

	nix_ctx = rvu_dl->rvu_nix_health_reporter->nix_event_ctx;

	वापस ctx ? rvu_nix_report_show(fmsg, ctx, NIX_AF_RVU_ERR) :
		     rvu_nix_report_show(fmsg, nix_ctx, NIX_AF_RVU_ERR);
पूर्ण

अटल पूर्णांक rvu_hw_nix_err_recover(काष्ठा devlink_health_reporter *reporter,
				  व्योम *ctx, काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_nix_event_ctx *nix_event_ctx = ctx;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, 0);
	अगर (blkaddr < 0)
		वापस blkaddr;

	अगर (nix_event_ctx->nix_af_rvu_err)
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_ERR_INT_ENA_W1S, ~0ULL);

	वापस 0;
पूर्ण

अटल पूर्णांक rvu_hw_nix_ras_dump(काष्ठा devlink_health_reporter *reporter,
			       काष्ठा devlink_fmsg *fmsg, व्योम *ctx,
			       काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_devlink *rvu_dl = rvu->rvu_dl;
	काष्ठा rvu_nix_event_ctx *nix_ctx;

	nix_ctx = rvu_dl->rvu_nix_health_reporter->nix_event_ctx;

	वापस ctx ? rvu_nix_report_show(fmsg, ctx, NIX_AF_RVU_RAS) :
		     rvu_nix_report_show(fmsg, nix_ctx, NIX_AF_RVU_RAS);
पूर्ण

अटल पूर्णांक rvu_hw_nix_ras_recover(काष्ठा devlink_health_reporter *reporter,
				  व्योम *ctx, काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_nix_event_ctx *nix_event_ctx = ctx;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, 0);
	अगर (blkaddr < 0)
		वापस blkaddr;

	अगर (nix_event_ctx->nix_af_rvu_पूर्णांक)
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RAS_ENA_W1S, ~0ULL);

	वापस 0;
पूर्ण

RVU_REPORTERS(hw_nix_पूर्णांकr);
RVU_REPORTERS(hw_nix_gen);
RVU_REPORTERS(hw_nix_err);
RVU_REPORTERS(hw_nix_ras);

अटल व्योम rvu_nix_health_reporters_destroy(काष्ठा rvu_devlink *rvu_dl);

अटल पूर्णांक rvu_nix_रेजिस्टर_reporters(काष्ठा rvu_devlink *rvu_dl)
अणु
	काष्ठा rvu_nix_health_reporters *rvu_reporters;
	काष्ठा rvu_nix_event_ctx *nix_event_context;
	काष्ठा rvu *rvu = rvu_dl->rvu;

	rvu_reporters = kzalloc(माप(*rvu_reporters), GFP_KERNEL);
	अगर (!rvu_reporters)
		वापस -ENOMEM;

	rvu_dl->rvu_nix_health_reporter = rvu_reporters;
	nix_event_context = kzalloc(माप(*nix_event_context), GFP_KERNEL);
	अगर (!nix_event_context)
		वापस -ENOMEM;

	rvu_reporters->nix_event_ctx = nix_event_context;
	rvu_reporters->rvu_hw_nix_पूर्णांकr_reporter =
		devlink_health_reporter_create(rvu_dl->dl, &rvu_hw_nix_पूर्णांकr_reporter_ops, 0, rvu);
	अगर (IS_ERR(rvu_reporters->rvu_hw_nix_पूर्णांकr_reporter)) अणु
		dev_warn(rvu->dev, "Failed to create hw_nix_intr reporter, err=%ld\n",
			 PTR_ERR(rvu_reporters->rvu_hw_nix_पूर्णांकr_reporter));
		वापस PTR_ERR(rvu_reporters->rvu_hw_nix_पूर्णांकr_reporter);
	पूर्ण

	rvu_reporters->rvu_hw_nix_gen_reporter =
		devlink_health_reporter_create(rvu_dl->dl, &rvu_hw_nix_gen_reporter_ops, 0, rvu);
	अगर (IS_ERR(rvu_reporters->rvu_hw_nix_gen_reporter)) अणु
		dev_warn(rvu->dev, "Failed to create hw_nix_gen reporter, err=%ld\n",
			 PTR_ERR(rvu_reporters->rvu_hw_nix_gen_reporter));
		वापस PTR_ERR(rvu_reporters->rvu_hw_nix_gen_reporter);
	पूर्ण

	rvu_reporters->rvu_hw_nix_err_reporter =
		devlink_health_reporter_create(rvu_dl->dl, &rvu_hw_nix_err_reporter_ops, 0, rvu);
	अगर (IS_ERR(rvu_reporters->rvu_hw_nix_err_reporter)) अणु
		dev_warn(rvu->dev, "Failed to create hw_nix_err reporter, err=%ld\n",
			 PTR_ERR(rvu_reporters->rvu_hw_nix_err_reporter));
		वापस PTR_ERR(rvu_reporters->rvu_hw_nix_err_reporter);
	पूर्ण

	rvu_reporters->rvu_hw_nix_ras_reporter =
		devlink_health_reporter_create(rvu_dl->dl, &rvu_hw_nix_ras_reporter_ops, 0, rvu);
	अगर (IS_ERR(rvu_reporters->rvu_hw_nix_ras_reporter)) अणु
		dev_warn(rvu->dev, "Failed to create hw_nix_ras reporter, err=%ld\n",
			 PTR_ERR(rvu_reporters->rvu_hw_nix_ras_reporter));
		वापस PTR_ERR(rvu_reporters->rvu_hw_nix_ras_reporter);
	पूर्ण

	rvu_dl->devlink_wq = create_workqueue("rvu_devlink_wq");
	अगर (!rvu_dl->devlink_wq)
		जाओ err;

	INIT_WORK(&rvu_reporters->पूर्णांकr_work, rvu_nix_पूर्णांकr_work);
	INIT_WORK(&rvu_reporters->gen_work, rvu_nix_gen_work);
	INIT_WORK(&rvu_reporters->err_work, rvu_nix_err_work);
	INIT_WORK(&rvu_reporters->ras_work, rvu_nix_ras_work);

	वापस 0;
err:
	rvu_nix_health_reporters_destroy(rvu_dl);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक rvu_nix_health_reporters_create(काष्ठा rvu_devlink *rvu_dl)
अणु
	काष्ठा rvu *rvu = rvu_dl->rvu;
	पूर्णांक err;

	err = rvu_nix_रेजिस्टर_reporters(rvu_dl);
	अगर (err) अणु
		dev_warn(rvu->dev, "Failed to create nix reporter, err =%d\n",
			 err);
		वापस err;
	पूर्ण
	rvu_nix_रेजिस्टर_पूर्णांकerrupts(rvu);

	वापस 0;
पूर्ण

अटल व्योम rvu_nix_health_reporters_destroy(काष्ठा rvu_devlink *rvu_dl)
अणु
	काष्ठा rvu_nix_health_reporters *nix_reporters;
	काष्ठा rvu *rvu = rvu_dl->rvu;

	nix_reporters = rvu_dl->rvu_nix_health_reporter;

	अगर (!nix_reporters->rvu_hw_nix_ras_reporter)
		वापस;
	अगर (!IS_ERR_OR_शून्य(nix_reporters->rvu_hw_nix_पूर्णांकr_reporter))
		devlink_health_reporter_destroy(nix_reporters->rvu_hw_nix_पूर्णांकr_reporter);

	अगर (!IS_ERR_OR_शून्य(nix_reporters->rvu_hw_nix_gen_reporter))
		devlink_health_reporter_destroy(nix_reporters->rvu_hw_nix_gen_reporter);

	अगर (!IS_ERR_OR_शून्य(nix_reporters->rvu_hw_nix_err_reporter))
		devlink_health_reporter_destroy(nix_reporters->rvu_hw_nix_err_reporter);

	अगर (!IS_ERR_OR_शून्य(nix_reporters->rvu_hw_nix_ras_reporter))
		devlink_health_reporter_destroy(nix_reporters->rvu_hw_nix_ras_reporter);

	rvu_nix_unरेजिस्टर_पूर्णांकerrupts(rvu);
	kमुक्त(rvu_dl->rvu_nix_health_reporter->nix_event_ctx);
	kमुक्त(rvu_dl->rvu_nix_health_reporter);
पूर्ण

अटल व्योम rvu_npa_पूर्णांकr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rvu_npa_health_reporters *rvu_npa_health_reporter;

	rvu_npa_health_reporter = container_of(work, काष्ठा rvu_npa_health_reporters, पूर्णांकr_work);
	devlink_health_report(rvu_npa_health_reporter->rvu_hw_npa_पूर्णांकr_reporter,
			      "NPA_AF_RVU Error",
			      rvu_npa_health_reporter->npa_event_ctx);
पूर्ण

अटल irqवापस_t rvu_npa_af_rvu_पूर्णांकr_handler(पूर्णांक irq, व्योम *rvu_irq)
अणु
	काष्ठा rvu_npa_event_ctx *npa_event_context;
	काष्ठा rvu_devlink *rvu_dl = rvu_irq;
	काष्ठा rvu *rvu;
	पूर्णांक blkaddr;
	u64 पूर्णांकr;

	rvu = rvu_dl->rvu;
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPA, 0);
	अगर (blkaddr < 0)
		वापस IRQ_NONE;

	npa_event_context = rvu_dl->rvu_npa_health_reporter->npa_event_ctx;
	पूर्णांकr = rvu_पढ़ो64(rvu, blkaddr, NPA_AF_RVU_INT);
	npa_event_context->npa_af_rvu_पूर्णांक = पूर्णांकr;

	/* Clear पूर्णांकerrupts */
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_RVU_INT, पूर्णांकr);
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_RVU_INT_ENA_W1C, ~0ULL);
	queue_work(rvu_dl->devlink_wq, &rvu_dl->rvu_npa_health_reporter->पूर्णांकr_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rvu_npa_gen_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rvu_npa_health_reporters *rvu_npa_health_reporter;

	rvu_npa_health_reporter = container_of(work, काष्ठा rvu_npa_health_reporters, gen_work);
	devlink_health_report(rvu_npa_health_reporter->rvu_hw_npa_gen_reporter,
			      "NPA_AF_GEN Error",
			      rvu_npa_health_reporter->npa_event_ctx);
पूर्ण

अटल irqवापस_t rvu_npa_af_gen_पूर्णांकr_handler(पूर्णांक irq, व्योम *rvu_irq)
अणु
	काष्ठा rvu_npa_event_ctx *npa_event_context;
	काष्ठा rvu_devlink *rvu_dl = rvu_irq;
	काष्ठा rvu *rvu;
	पूर्णांक blkaddr;
	u64 पूर्णांकr;

	rvu = rvu_dl->rvu;
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPA, 0);
	अगर (blkaddr < 0)
		वापस IRQ_NONE;

	npa_event_context = rvu_dl->rvu_npa_health_reporter->npa_event_ctx;
	पूर्णांकr = rvu_पढ़ो64(rvu, blkaddr, NPA_AF_GEN_INT);
	npa_event_context->npa_af_rvu_gen = पूर्णांकr;

	/* Clear पूर्णांकerrupts */
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_GEN_INT, पूर्णांकr);
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_GEN_INT_ENA_W1C, ~0ULL);
	queue_work(rvu_dl->devlink_wq, &rvu_dl->rvu_npa_health_reporter->gen_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rvu_npa_err_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rvu_npa_health_reporters *rvu_npa_health_reporter;

	rvu_npa_health_reporter = container_of(work, काष्ठा rvu_npa_health_reporters, err_work);
	devlink_health_report(rvu_npa_health_reporter->rvu_hw_npa_err_reporter,
			      "NPA_AF_ERR Error",
			      rvu_npa_health_reporter->npa_event_ctx);
पूर्ण

अटल irqवापस_t rvu_npa_af_err_पूर्णांकr_handler(पूर्णांक irq, व्योम *rvu_irq)
अणु
	काष्ठा rvu_npa_event_ctx *npa_event_context;
	काष्ठा rvu_devlink *rvu_dl = rvu_irq;
	काष्ठा rvu *rvu;
	पूर्णांक blkaddr;
	u64 पूर्णांकr;

	rvu = rvu_dl->rvu;
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPA, 0);
	अगर (blkaddr < 0)
		वापस IRQ_NONE;
	npa_event_context = rvu_dl->rvu_npa_health_reporter->npa_event_ctx;
	पूर्णांकr = rvu_पढ़ो64(rvu, blkaddr, NPA_AF_ERR_INT);
	npa_event_context->npa_af_rvu_err = पूर्णांकr;

	/* Clear पूर्णांकerrupts */
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_ERR_INT, पूर्णांकr);
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_ERR_INT_ENA_W1C, ~0ULL);
	queue_work(rvu_dl->devlink_wq, &rvu_dl->rvu_npa_health_reporter->err_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rvu_npa_ras_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rvu_npa_health_reporters *rvu_npa_health_reporter;

	rvu_npa_health_reporter = container_of(work, काष्ठा rvu_npa_health_reporters, ras_work);
	devlink_health_report(rvu_npa_health_reporter->rvu_hw_npa_ras_reporter,
			      "HW NPA_AF_RAS Error reported",
			      rvu_npa_health_reporter->npa_event_ctx);
पूर्ण

अटल irqवापस_t rvu_npa_af_ras_पूर्णांकr_handler(पूर्णांक irq, व्योम *rvu_irq)
अणु
	काष्ठा rvu_npa_event_ctx *npa_event_context;
	काष्ठा rvu_devlink *rvu_dl = rvu_irq;
	काष्ठा rvu *rvu;
	पूर्णांक blkaddr;
	u64 पूर्णांकr;

	rvu = rvu_dl->rvu;
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPA, 0);
	अगर (blkaddr < 0)
		वापस IRQ_NONE;

	npa_event_context = rvu_dl->rvu_npa_health_reporter->npa_event_ctx;
	पूर्णांकr = rvu_पढ़ो64(rvu, blkaddr, NPA_AF_RAS);
	npa_event_context->npa_af_rvu_ras = पूर्णांकr;

	/* Clear पूर्णांकerrupts */
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_RAS, पूर्णांकr);
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_RAS_ENA_W1C, ~0ULL);
	queue_work(rvu_dl->devlink_wq, &rvu_dl->rvu_npa_health_reporter->ras_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rvu_npa_unरेजिस्टर_पूर्णांकerrupts(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_devlink *rvu_dl = rvu->rvu_dl;
	पूर्णांक i, offs, blkaddr;
	u64 reg;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPA, 0);
	अगर (blkaddr < 0)
		वापस;

	reg = rvu_पढ़ो64(rvu, blkaddr, NPA_PRIV_AF_INT_CFG);
	offs = reg & 0x3FF;

	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_RVU_INT_ENA_W1C, ~0ULL);
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_GEN_INT_ENA_W1C, ~0ULL);
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_ERR_INT_ENA_W1C, ~0ULL);
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_RAS_ENA_W1C, ~0ULL);

	क्रम (i = 0; i < NPA_AF_INT_VEC_CNT; i++)
		अगर (rvu->irq_allocated[offs + i]) अणु
			मुक्त_irq(pci_irq_vector(rvu->pdev, offs + i), rvu_dl);
			rvu->irq_allocated[offs + i] = false;
		पूर्ण
पूर्ण

अटल पूर्णांक rvu_npa_रेजिस्टर_पूर्णांकerrupts(काष्ठा rvu *rvu)
अणु
	पूर्णांक blkaddr, base;
	bool rc;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPA, 0);
	अगर (blkaddr < 0)
		वापस blkaddr;

	/* Get NPA AF MSIX vectors offset. */
	base = rvu_पढ़ो64(rvu, blkaddr, NPA_PRIV_AF_INT_CFG) & 0x3ff;
	अगर (!base) अणु
		dev_warn(rvu->dev,
			 "Failed to get NPA_AF_INT vector offsets\n");
		वापस 0;
	पूर्ण

	/* Register and enable NPA_AF_RVU_INT पूर्णांकerrupt */
	rc = rvu_common_request_irq(rvu, base +  NPA_AF_INT_VEC_RVU,
				    "NPA_AF_RVU_INT",
				    rvu_npa_af_rvu_पूर्णांकr_handler);
	अगर (!rc)
		जाओ err;
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_RVU_INT_ENA_W1S, ~0ULL);

	/* Register and enable NPA_AF_GEN_INT पूर्णांकerrupt */
	rc = rvu_common_request_irq(rvu, base + NPA_AF_INT_VEC_GEN,
				    "NPA_AF_RVU_GEN",
				    rvu_npa_af_gen_पूर्णांकr_handler);
	अगर (!rc)
		जाओ err;
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_GEN_INT_ENA_W1S, ~0ULL);

	/* Register and enable NPA_AF_ERR_INT पूर्णांकerrupt */
	rc = rvu_common_request_irq(rvu, base + NPA_AF_INT_VEC_AF_ERR,
				    "NPA_AF_ERR_INT",
				    rvu_npa_af_err_पूर्णांकr_handler);
	अगर (!rc)
		जाओ err;
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_ERR_INT_ENA_W1S, ~0ULL);

	/* Register and enable NPA_AF_RAS पूर्णांकerrupt */
	rc = rvu_common_request_irq(rvu, base + NPA_AF_INT_VEC_POISON,
				    "NPA_AF_RAS",
				    rvu_npa_af_ras_पूर्णांकr_handler);
	अगर (!rc)
		जाओ err;
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_RAS_ENA_W1S, ~0ULL);

	वापस 0;
err:
	rvu_npa_unरेजिस्टर_पूर्णांकerrupts(rvu);
	वापस rc;
पूर्ण

अटल पूर्णांक rvu_npa_report_show(काष्ठा devlink_fmsg *fmsg, व्योम *ctx,
			       क्रमागत npa_af_rvu_health health_reporter)
अणु
	काष्ठा rvu_npa_event_ctx *npa_event_context;
	अचिन्हित पूर्णांक alloc_dis, मुक्त_dis;
	u64 पूर्णांकr_val;
	पूर्णांक err;

	npa_event_context = ctx;
	चयन (health_reporter) अणु
	हाल NPA_AF_RVU_GEN:
		पूर्णांकr_val = npa_event_context->npa_af_rvu_gen;
		err = rvu_report_pair_start(fmsg, "NPA_AF_GENERAL");
		अगर (err)
			वापस err;
		err = devlink_fmsg_u64_pair_put(fmsg, "\tNPA General Interrupt Reg ",
						npa_event_context->npa_af_rvu_gen);
		अगर (err)
			वापस err;
		अगर (पूर्णांकr_val & BIT_ULL(32)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tUnmap PF Error");
			अगर (err)
				वापस err;
		पूर्ण

		मुक्त_dis = FIELD_GET(GENMASK(15, 0), पूर्णांकr_val);
		अगर (मुक्त_dis & BIT(NPA_INPQ_NIX0_RX)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tNIX0: free disabled RX");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (मुक्त_dis & BIT(NPA_INPQ_NIX0_TX)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tNIX0:free disabled TX");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (मुक्त_dis & BIT(NPA_INPQ_NIX1_RX)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tNIX1: free disabled RX");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (मुक्त_dis & BIT(NPA_INPQ_NIX1_TX)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tNIX1:free disabled TX");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (मुक्त_dis & BIT(NPA_INPQ_SSO)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tFree Disabled for SSO");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (मुक्त_dis & BIT(NPA_INPQ_TIM)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tFree Disabled for TIM");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (मुक्त_dis & BIT(NPA_INPQ_DPI)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tFree Disabled for DPI");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (मुक्त_dis & BIT(NPA_INPQ_AURA_OP)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tFree Disabled for AURA");
			अगर (err)
				वापस err;
		पूर्ण

		alloc_dis = FIELD_GET(GENMASK(31, 16), पूर्णांकr_val);
		अगर (alloc_dis & BIT(NPA_INPQ_NIX0_RX)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tNIX0: alloc disabled RX");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (alloc_dis & BIT(NPA_INPQ_NIX0_TX)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tNIX0:alloc disabled TX");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (alloc_dis & BIT(NPA_INPQ_NIX1_RX)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tNIX1: alloc disabled RX");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (alloc_dis & BIT(NPA_INPQ_NIX1_TX)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tNIX1:alloc disabled TX");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (alloc_dis & BIT(NPA_INPQ_SSO)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tAlloc Disabled for SSO");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (alloc_dis & BIT(NPA_INPQ_TIM)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tAlloc Disabled for TIM");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (alloc_dis & BIT(NPA_INPQ_DPI)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tAlloc Disabled for DPI");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (alloc_dis & BIT(NPA_INPQ_AURA_OP)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tAlloc Disabled for AURA");
			अगर (err)
				वापस err;
		पूर्ण
		err = rvu_report_pair_end(fmsg);
		अगर (err)
			वापस err;
		अवरोध;
	हाल NPA_AF_RVU_ERR:
		err = rvu_report_pair_start(fmsg, "NPA_AF_ERR");
		अगर (err)
			वापस err;
		err = devlink_fmsg_u64_pair_put(fmsg, "\tNPA Error Interrupt Reg ",
						npa_event_context->npa_af_rvu_err);
		अगर (err)
			वापस err;

		अगर (npa_event_context->npa_af_rvu_err & BIT_ULL(14)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tFault on NPA_AQ_INST_S read");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (npa_event_context->npa_af_rvu_err & BIT_ULL(13)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tFault on NPA_AQ_RES_S write");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (npa_event_context->npa_af_rvu_err & BIT_ULL(12)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tAQ Doorbell Error");
			अगर (err)
				वापस err;
		पूर्ण
		err = rvu_report_pair_end(fmsg);
		अगर (err)
			वापस err;
		अवरोध;
	हाल NPA_AF_RVU_RAS:
		err = rvu_report_pair_start(fmsg, "NPA_AF_RVU_RAS");
		अगर (err)
			वापस err;
		err = devlink_fmsg_u64_pair_put(fmsg, "\tNPA RAS Interrupt Reg ",
						npa_event_context->npa_af_rvu_ras);
		अगर (err)
			वापस err;
		अगर (npa_event_context->npa_af_rvu_ras & BIT_ULL(34)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tPoison data on NPA_AQ_INST_S");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (npa_event_context->npa_af_rvu_ras & BIT_ULL(33)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tPoison data on NPA_AQ_RES_S");
			अगर (err)
				वापस err;
		पूर्ण
		अगर (npa_event_context->npa_af_rvu_ras & BIT_ULL(32)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tPoison data on HW context");
			अगर (err)
				वापस err;
		पूर्ण
		err = rvu_report_pair_end(fmsg);
		अगर (err)
			वापस err;
		अवरोध;
	हाल NPA_AF_RVU_INTR:
		err = rvu_report_pair_start(fmsg, "NPA_AF_RVU");
		अगर (err)
			वापस err;
		err = devlink_fmsg_u64_pair_put(fmsg, "\tNPA RVU Interrupt Reg ",
						npa_event_context->npa_af_rvu_पूर्णांक);
		अगर (err)
			वापस err;
		अगर (npa_event_context->npa_af_rvu_पूर्णांक & BIT_ULL(0)) अणु
			err = devlink_fmsg_string_put(fmsg, "\n\tUnmap Slot Error");
			अगर (err)
				वापस err;
		पूर्ण
		वापस rvu_report_pair_end(fmsg);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rvu_hw_npa_पूर्णांकr_dump(काष्ठा devlink_health_reporter *reporter,
				काष्ठा devlink_fmsg *fmsg, व्योम *ctx,
				काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_devlink *rvu_dl = rvu->rvu_dl;
	काष्ठा rvu_npa_event_ctx *npa_ctx;

	npa_ctx = rvu_dl->rvu_npa_health_reporter->npa_event_ctx;

	वापस ctx ? rvu_npa_report_show(fmsg, ctx, NPA_AF_RVU_INTR) :
		     rvu_npa_report_show(fmsg, npa_ctx, NPA_AF_RVU_INTR);
पूर्ण

अटल पूर्णांक rvu_hw_npa_पूर्णांकr_recover(काष्ठा devlink_health_reporter *reporter,
				   व्योम *ctx, काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_npa_event_ctx *npa_event_ctx = ctx;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPA, 0);
	अगर (blkaddr < 0)
		वापस blkaddr;

	अगर (npa_event_ctx->npa_af_rvu_पूर्णांक)
		rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_RVU_INT_ENA_W1S, ~0ULL);

	वापस 0;
पूर्ण

अटल पूर्णांक rvu_hw_npa_gen_dump(काष्ठा devlink_health_reporter *reporter,
			       काष्ठा devlink_fmsg *fmsg, व्योम *ctx,
			       काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_devlink *rvu_dl = rvu->rvu_dl;
	काष्ठा rvu_npa_event_ctx *npa_ctx;

	npa_ctx = rvu_dl->rvu_npa_health_reporter->npa_event_ctx;

	वापस ctx ? rvu_npa_report_show(fmsg, ctx, NPA_AF_RVU_GEN) :
		     rvu_npa_report_show(fmsg, npa_ctx, NPA_AF_RVU_GEN);
पूर्ण

अटल पूर्णांक rvu_hw_npa_gen_recover(काष्ठा devlink_health_reporter *reporter,
				  व्योम *ctx, काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_npa_event_ctx *npa_event_ctx = ctx;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPA, 0);
	अगर (blkaddr < 0)
		वापस blkaddr;

	अगर (npa_event_ctx->npa_af_rvu_gen)
		rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_GEN_INT_ENA_W1S, ~0ULL);

	वापस 0;
पूर्ण

अटल पूर्णांक rvu_hw_npa_err_dump(काष्ठा devlink_health_reporter *reporter,
			       काष्ठा devlink_fmsg *fmsg, व्योम *ctx,
			       काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_devlink *rvu_dl = rvu->rvu_dl;
	काष्ठा rvu_npa_event_ctx *npa_ctx;

	npa_ctx = rvu_dl->rvu_npa_health_reporter->npa_event_ctx;

	वापस ctx ? rvu_npa_report_show(fmsg, ctx, NPA_AF_RVU_ERR) :
		     rvu_npa_report_show(fmsg, npa_ctx, NPA_AF_RVU_ERR);
पूर्ण

अटल पूर्णांक rvu_hw_npa_err_recover(काष्ठा devlink_health_reporter *reporter,
				  व्योम *ctx, काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_npa_event_ctx *npa_event_ctx = ctx;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPA, 0);
	अगर (blkaddr < 0)
		वापस blkaddr;

	अगर (npa_event_ctx->npa_af_rvu_err)
		rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_ERR_INT_ENA_W1S, ~0ULL);

	वापस 0;
पूर्ण

अटल पूर्णांक rvu_hw_npa_ras_dump(काष्ठा devlink_health_reporter *reporter,
			       काष्ठा devlink_fmsg *fmsg, व्योम *ctx,
			       काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_devlink *rvu_dl = rvu->rvu_dl;
	काष्ठा rvu_npa_event_ctx *npa_ctx;

	npa_ctx = rvu_dl->rvu_npa_health_reporter->npa_event_ctx;

	वापस ctx ? rvu_npa_report_show(fmsg, ctx, NPA_AF_RVU_RAS) :
		     rvu_npa_report_show(fmsg, npa_ctx, NPA_AF_RVU_RAS);
पूर्ण

अटल पूर्णांक rvu_hw_npa_ras_recover(काष्ठा devlink_health_reporter *reporter,
				  व्योम *ctx, काष्ठा netlink_ext_ack *netlink_extack)
अणु
	काष्ठा rvu *rvu = devlink_health_reporter_priv(reporter);
	काष्ठा rvu_npa_event_ctx *npa_event_ctx = ctx;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPA, 0);
	अगर (blkaddr < 0)
		वापस blkaddr;

	अगर (npa_event_ctx->npa_af_rvu_ras)
		rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_RAS_ENA_W1S, ~0ULL);

	वापस 0;
पूर्ण

RVU_REPORTERS(hw_npa_पूर्णांकr);
RVU_REPORTERS(hw_npa_gen);
RVU_REPORTERS(hw_npa_err);
RVU_REPORTERS(hw_npa_ras);

अटल व्योम rvu_npa_health_reporters_destroy(काष्ठा rvu_devlink *rvu_dl);

अटल पूर्णांक rvu_npa_रेजिस्टर_reporters(काष्ठा rvu_devlink *rvu_dl)
अणु
	काष्ठा rvu_npa_health_reporters *rvu_reporters;
	काष्ठा rvu_npa_event_ctx *npa_event_context;
	काष्ठा rvu *rvu = rvu_dl->rvu;

	rvu_reporters = kzalloc(माप(*rvu_reporters), GFP_KERNEL);
	अगर (!rvu_reporters)
		वापस -ENOMEM;

	rvu_dl->rvu_npa_health_reporter = rvu_reporters;
	npa_event_context = kzalloc(माप(*npa_event_context), GFP_KERNEL);
	अगर (!npa_event_context)
		वापस -ENOMEM;

	rvu_reporters->npa_event_ctx = npa_event_context;
	rvu_reporters->rvu_hw_npa_पूर्णांकr_reporter =
		devlink_health_reporter_create(rvu_dl->dl, &rvu_hw_npa_पूर्णांकr_reporter_ops, 0, rvu);
	अगर (IS_ERR(rvu_reporters->rvu_hw_npa_पूर्णांकr_reporter)) अणु
		dev_warn(rvu->dev, "Failed to create hw_npa_intr reporter, err=%ld\n",
			 PTR_ERR(rvu_reporters->rvu_hw_npa_पूर्णांकr_reporter));
		वापस PTR_ERR(rvu_reporters->rvu_hw_npa_पूर्णांकr_reporter);
	पूर्ण

	rvu_reporters->rvu_hw_npa_gen_reporter =
		devlink_health_reporter_create(rvu_dl->dl, &rvu_hw_npa_gen_reporter_ops, 0, rvu);
	अगर (IS_ERR(rvu_reporters->rvu_hw_npa_gen_reporter)) अणु
		dev_warn(rvu->dev, "Failed to create hw_npa_gen reporter, err=%ld\n",
			 PTR_ERR(rvu_reporters->rvu_hw_npa_gen_reporter));
		वापस PTR_ERR(rvu_reporters->rvu_hw_npa_gen_reporter);
	पूर्ण

	rvu_reporters->rvu_hw_npa_err_reporter =
		devlink_health_reporter_create(rvu_dl->dl, &rvu_hw_npa_err_reporter_ops, 0, rvu);
	अगर (IS_ERR(rvu_reporters->rvu_hw_npa_err_reporter)) अणु
		dev_warn(rvu->dev, "Failed to create hw_npa_err reporter, err=%ld\n",
			 PTR_ERR(rvu_reporters->rvu_hw_npa_err_reporter));
		वापस PTR_ERR(rvu_reporters->rvu_hw_npa_err_reporter);
	पूर्ण

	rvu_reporters->rvu_hw_npa_ras_reporter =
		devlink_health_reporter_create(rvu_dl->dl, &rvu_hw_npa_ras_reporter_ops, 0, rvu);
	अगर (IS_ERR(rvu_reporters->rvu_hw_npa_ras_reporter)) अणु
		dev_warn(rvu->dev, "Failed to create hw_npa_ras reporter, err=%ld\n",
			 PTR_ERR(rvu_reporters->rvu_hw_npa_ras_reporter));
		वापस PTR_ERR(rvu_reporters->rvu_hw_npa_ras_reporter);
	पूर्ण

	rvu_dl->devlink_wq = create_workqueue("rvu_devlink_wq");
	अगर (!rvu_dl->devlink_wq)
		जाओ err;

	INIT_WORK(&rvu_reporters->पूर्णांकr_work, rvu_npa_पूर्णांकr_work);
	INIT_WORK(&rvu_reporters->err_work, rvu_npa_err_work);
	INIT_WORK(&rvu_reporters->gen_work, rvu_npa_gen_work);
	INIT_WORK(&rvu_reporters->ras_work, rvu_npa_ras_work);

	वापस 0;
err:
	rvu_npa_health_reporters_destroy(rvu_dl);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक rvu_npa_health_reporters_create(काष्ठा rvu_devlink *rvu_dl)
अणु
	काष्ठा rvu *rvu = rvu_dl->rvu;
	पूर्णांक err;

	err = rvu_npa_रेजिस्टर_reporters(rvu_dl);
	अगर (err) अणु
		dev_warn(rvu->dev, "Failed to create npa reporter, err =%d\n",
			 err);
		वापस err;
	पूर्ण
	rvu_npa_रेजिस्टर_पूर्णांकerrupts(rvu);

	वापस 0;
पूर्ण

अटल व्योम rvu_npa_health_reporters_destroy(काष्ठा rvu_devlink *rvu_dl)
अणु
	काष्ठा rvu_npa_health_reporters *npa_reporters;
	काष्ठा rvu *rvu = rvu_dl->rvu;

	npa_reporters = rvu_dl->rvu_npa_health_reporter;

	अगर (!npa_reporters->rvu_hw_npa_ras_reporter)
		वापस;
	अगर (!IS_ERR_OR_शून्य(npa_reporters->rvu_hw_npa_पूर्णांकr_reporter))
		devlink_health_reporter_destroy(npa_reporters->rvu_hw_npa_पूर्णांकr_reporter);

	अगर (!IS_ERR_OR_शून्य(npa_reporters->rvu_hw_npa_gen_reporter))
		devlink_health_reporter_destroy(npa_reporters->rvu_hw_npa_gen_reporter);

	अगर (!IS_ERR_OR_शून्य(npa_reporters->rvu_hw_npa_err_reporter))
		devlink_health_reporter_destroy(npa_reporters->rvu_hw_npa_err_reporter);

	अगर (!IS_ERR_OR_शून्य(npa_reporters->rvu_hw_npa_ras_reporter))
		devlink_health_reporter_destroy(npa_reporters->rvu_hw_npa_ras_reporter);

	rvu_npa_unरेजिस्टर_पूर्णांकerrupts(rvu);
	kमुक्त(rvu_dl->rvu_npa_health_reporter->npa_event_ctx);
	kमुक्त(rvu_dl->rvu_npa_health_reporter);
पूर्ण

अटल पूर्णांक rvu_health_reporters_create(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_devlink *rvu_dl;
	पूर्णांक err;

	rvu_dl = rvu->rvu_dl;
	err = rvu_npa_health_reporters_create(rvu_dl);
	अगर (err)
		वापस err;

	वापस rvu_nix_health_reporters_create(rvu_dl);
पूर्ण

अटल व्योम rvu_health_reporters_destroy(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_devlink *rvu_dl;

	अगर (!rvu->rvu_dl)
		वापस;

	rvu_dl = rvu->rvu_dl;
	rvu_npa_health_reporters_destroy(rvu_dl);
	rvu_nix_health_reporters_destroy(rvu_dl);
पूर्ण

अटल पूर्णांक rvu_devlink_info_get(काष्ठा devlink *devlink, काष्ठा devlink_info_req *req,
				काष्ठा netlink_ext_ack *extack)
अणु
	वापस devlink_info_driver_name_put(req, DRV_NAME);
पूर्ण

अटल स्थिर काष्ठा devlink_ops rvu_devlink_ops = अणु
	.info_get = rvu_devlink_info_get,
पूर्ण;

पूर्णांक rvu_रेजिस्टर_dl(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_devlink *rvu_dl;
	काष्ठा devlink *dl;
	पूर्णांक err;

	rvu_dl = kzalloc(माप(*rvu_dl), GFP_KERNEL);
	अगर (!rvu_dl)
		वापस -ENOMEM;

	dl = devlink_alloc(&rvu_devlink_ops, माप(काष्ठा rvu_devlink));
	अगर (!dl) अणु
		dev_warn(rvu->dev, "devlink_alloc failed\n");
		kमुक्त(rvu_dl);
		वापस -ENOMEM;
	पूर्ण

	err = devlink_रेजिस्टर(dl, rvu->dev);
	अगर (err) अणु
		dev_err(rvu->dev, "devlink register failed with error %d\n", err);
		devlink_मुक्त(dl);
		kमुक्त(rvu_dl);
		वापस err;
	पूर्ण

	rvu_dl->dl = dl;
	rvu_dl->rvu = rvu;
	rvu->rvu_dl = rvu_dl;

	वापस rvu_health_reporters_create(rvu);
पूर्ण

व्योम rvu_unरेजिस्टर_dl(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_devlink *rvu_dl = rvu->rvu_dl;
	काष्ठा devlink *dl = rvu_dl->dl;

	अगर (!dl)
		वापस;

	rvu_health_reporters_destroy(rvu);
	devlink_unरेजिस्टर(dl);
	devlink_मुक्त(dl);
	kमुक्त(rvu_dl);
पूर्ण
