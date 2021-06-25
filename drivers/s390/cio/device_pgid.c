<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  CCW device PGID and path verअगरication I/O handling.
 *
 *    Copyright IBM Corp. 2002, 2009
 *    Author(s): Cornelia Huck <cornelia.huck@de.ibm.com>
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>
 *		 Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/bitops.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/cपन.स>

#समावेश "cio.h"
#समावेश "cio_debug.h"
#समावेश "device.h"
#समावेश "io_sch.h"

#घोषणा PGID_RETRIES	256
#घोषणा PGID_TIMEOUT	(10 * HZ)

अटल व्योम verअगरy_start(काष्ठा ccw_device *cdev);

/*
 * Process path verअगरication data and report result.
 */
अटल व्योम verअगरy_करोne(काष्ठा ccw_device *cdev, पूर्णांक rc)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा ccw_dev_id *id = &cdev->निजी->dev_id;
	पूर्णांक mpath = cdev->निजी->flags.mpath;
	पूर्णांक pgroup = cdev->निजी->flags.pgroup;

	अगर (rc)
		जाओ out;
	/* Ensure consistent multipathing state at device and channel. */
	अगर (sch->config.mp != mpath) अणु
		sch->config.mp = mpath;
		rc = cio_commit_config(sch);
	पूर्ण
out:
	CIO_MSG_EVENT(2, "vrfy: device 0.%x.%04x: rc=%d pgroup=%d mpath=%d "
			 "vpm=%02x\n", id->ssid, id->devno, rc, pgroup, mpath,
			 sch->vpm);
	ccw_device_verअगरy_करोne(cdev, rc);
पूर्ण

/*
 * Create channel program to perक्रमm a NOOP.
 */
अटल व्योम nop_build_cp(काष्ठा ccw_device *cdev)
अणु
	काष्ठा ccw_request *req = &cdev->निजी->req;
	काष्ठा ccw1 *cp = cdev->निजी->dma_area->iccws;

	cp->cmd_code	= CCW_CMD_NOOP;
	cp->cda		= 0;
	cp->count	= 0;
	cp->flags	= CCW_FLAG_SLI;
	req->cp		= cp;
पूर्ण

/*
 * Perक्रमm NOOP on a single path.
 */
अटल व्योम nop_करो(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा ccw_request *req = &cdev->निजी->req;

	req->lpm = lpm_adjust(req->lpm, sch->schib.pmcw.pam & sch->opm &
			      ~cdev->निजी->path_noirq_mask);
	अगर (!req->lpm)
		जाओ out_nopath;
	nop_build_cp(cdev);
	ccw_request_start(cdev);
	वापस;

out_nopath:
	verअगरy_करोne(cdev, sch->vpm ? 0 : -EACCES);
पूर्ण

/*
 * Adjust NOOP I/O status.
 */
अटल क्रमागत io_status nop_filter(काष्ठा ccw_device *cdev, व्योम *data,
				 काष्ठा irb *irb, क्रमागत io_status status)
अणु
	/* Only subchannel status might indicate a path error. */
	अगर (status == IO_STATUS_ERROR && irb->scsw.cmd.cstat == 0)
		वापस IO_DONE;
	वापस status;
पूर्ण

/*
 * Process NOOP request result क्रम a single path.
 */
अटल व्योम nop_callback(काष्ठा ccw_device *cdev, व्योम *data, पूर्णांक rc)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा ccw_request *req = &cdev->निजी->req;

	चयन (rc) अणु
	हाल 0:
		sch->vpm |= req->lpm;
		अवरोध;
	हाल -ETIME:
		cdev->निजी->path_noirq_mask |= req->lpm;
		अवरोध;
	हाल -EACCES:
		cdev->निजी->path_notoper_mask |= req->lpm;
		अवरोध;
	शेष:
		जाओ err;
	पूर्ण
	/* Continue on the next path. */
	req->lpm >>= 1;
	nop_करो(cdev);
	वापस;

err:
	verअगरy_करोne(cdev, rc);
पूर्ण

/*
 * Create channel program to perक्रमm SET PGID on a single path.
 */
अटल व्योम spid_build_cp(काष्ठा ccw_device *cdev, u8 fn)
अणु
	काष्ठा ccw_request *req = &cdev->निजी->req;
	काष्ठा ccw1 *cp = cdev->निजी->dma_area->iccws;
	पूर्णांक i = pathmask_to_pos(req->lpm);
	काष्ठा pgid *pgid = &cdev->निजी->dma_area->pgid[i];

	pgid->inf.fc	= fn;
	cp->cmd_code	= CCW_CMD_SET_PGID;
	cp->cda		= (u32) (addr_t) pgid;
	cp->count	= माप(*pgid);
	cp->flags	= CCW_FLAG_SLI;
	req->cp		= cp;
पूर्ण

अटल व्योम pgid_wipeout_callback(काष्ठा ccw_device *cdev, व्योम *data, पूर्णांक rc)
अणु
	अगर (rc) अणु
		/* We करोn't know the path groups' state. Abort. */
		verअगरy_करोne(cdev, rc);
		वापस;
	पूर्ण
	/*
	 * Path groups have been reset. Restart path verअगरication but
	 * leave paths in path_noirq_mask out.
	 */
	cdev->निजी->flags.pgid_unknown = 0;
	verअगरy_start(cdev);
पूर्ण

/*
 * Reset pathgroups and restart path verअगरication, leave unusable paths out.
 */
अटल व्योम pgid_wipeout_start(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा ccw_dev_id *id = &cdev->निजी->dev_id;
	काष्ठा ccw_request *req = &cdev->निजी->req;
	u8 fn;

	CIO_MSG_EVENT(2, "wipe: device 0.%x.%04x: pvm=%02x nim=%02x\n",
		      id->ssid, id->devno, cdev->निजी->pgid_valid_mask,
		      cdev->निजी->path_noirq_mask);

	/* Initialize request data. */
	स_रखो(req, 0, माप(*req));
	req->समयout	= PGID_TIMEOUT;
	req->maxretries	= PGID_RETRIES;
	req->lpm	= sch->schib.pmcw.pam;
	req->callback	= pgid_wipeout_callback;
	fn = SPID_FUNC_DISBAND;
	अगर (cdev->निजी->flags.mpath)
		fn |= SPID_FUNC_MULTI_PATH;
	spid_build_cp(cdev, fn);
	ccw_request_start(cdev);
पूर्ण

/*
 * Perक्रमm establish/resign SET PGID on a single path.
 */
अटल व्योम spid_करो(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा ccw_request *req = &cdev->निजी->req;
	u8 fn;

	/* Use next available path that is not alपढ़ोy in correct state. */
	req->lpm = lpm_adjust(req->lpm, cdev->निजी->pgid_toकरो_mask);
	अगर (!req->lpm)
		जाओ out_nopath;
	/* Channel program setup. */
	अगर (req->lpm & sch->opm)
		fn = SPID_FUNC_ESTABLISH;
	अन्यथा
		fn = SPID_FUNC_RESIGN;
	अगर (cdev->निजी->flags.mpath)
		fn |= SPID_FUNC_MULTI_PATH;
	spid_build_cp(cdev, fn);
	ccw_request_start(cdev);
	वापस;

out_nopath:
	अगर (cdev->निजी->flags.pgid_unknown) अणु
		/* At least one SPID could be partially करोne. */
		pgid_wipeout_start(cdev);
		वापस;
	पूर्ण
	verअगरy_करोne(cdev, sch->vpm ? 0 : -EACCES);
पूर्ण

/*
 * Process SET PGID request result क्रम a single path.
 */
अटल व्योम spid_callback(काष्ठा ccw_device *cdev, व्योम *data, पूर्णांक rc)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा ccw_request *req = &cdev->निजी->req;

	चयन (rc) अणु
	हाल 0:
		sch->vpm |= req->lpm & sch->opm;
		अवरोध;
	हाल -ETIME:
		cdev->निजी->flags.pgid_unknown = 1;
		cdev->निजी->path_noirq_mask |= req->lpm;
		अवरोध;
	हाल -EACCES:
		cdev->निजी->path_notoper_mask |= req->lpm;
		अवरोध;
	हाल -EOPNOTSUPP:
		अगर (cdev->निजी->flags.mpath) अणु
			/* Try without multipathing. */
			cdev->निजी->flags.mpath = 0;
			जाओ out_restart;
		पूर्ण
		/* Try without pathgrouping. */
		cdev->निजी->flags.pgroup = 0;
		जाओ out_restart;
	शेष:
		जाओ err;
	पूर्ण
	req->lpm >>= 1;
	spid_करो(cdev);
	वापस;

out_restart:
	verअगरy_start(cdev);
	वापस;
err:
	verअगरy_करोne(cdev, rc);
पूर्ण

अटल व्योम spid_start(काष्ठा ccw_device *cdev)
अणु
	काष्ठा ccw_request *req = &cdev->निजी->req;

	/* Initialize request data. */
	स_रखो(req, 0, माप(*req));
	req->समयout	= PGID_TIMEOUT;
	req->maxretries	= PGID_RETRIES;
	req->lpm	= 0x80;
	req->singlepath	= 1;
	req->callback	= spid_callback;
	spid_करो(cdev);
पूर्ण

अटल पूर्णांक pgid_is_reset(काष्ठा pgid *p)
अणु
	अक्षर *c;

	क्रम (c = (अक्षर *)p + 1; c < (अक्षर *)(p + 1); c++) अणु
		अगर (*c != 0)
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक pgid_cmp(काष्ठा pgid *p1, काष्ठा pgid *p2)
अणु
	वापस स_भेद((अक्षर *) p1 + 1, (अक्षर *) p2 + 1,
		      माप(काष्ठा pgid) - 1);
पूर्ण

/*
 * Determine pathgroup state from PGID data.
 */
अटल व्योम pgid_analyze(काष्ठा ccw_device *cdev, काष्ठा pgid **p,
			 पूर्णांक *mismatch, u8 *reserved, u8 *reset)
अणु
	काष्ठा pgid *pgid = &cdev->निजी->dma_area->pgid[0];
	काष्ठा pgid *first = शून्य;
	पूर्णांक lpm;
	पूर्णांक i;

	*mismatch = 0;
	*reserved = 0;
	*reset = 0;
	क्रम (i = 0, lpm = 0x80; i < 8; i++, pgid++, lpm >>= 1) अणु
		अगर ((cdev->निजी->pgid_valid_mask & lpm) == 0)
			जारी;
		अगर (pgid->inf.ps.state2 == SNID_STATE2_RESVD_ELSE)
			*reserved |= lpm;
		अगर (pgid_is_reset(pgid)) अणु
			*reset |= lpm;
			जारी;
		पूर्ण
		अगर (!first) अणु
			first = pgid;
			जारी;
		पूर्ण
		अगर (pgid_cmp(pgid, first) != 0)
			*mismatch = 1;
	पूर्ण
	अगर (!first)
		first = &channel_subप्रणालीs[0]->global_pgid;
	*p = first;
पूर्ण

अटल u8 pgid_to_करोnepm(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा pgid *pgid;
	पूर्णांक i;
	पूर्णांक lpm;
	u8 करोnepm = 0;

	/* Set bits क्रम paths which are alपढ़ोy in the target state. */
	क्रम (i = 0; i < 8; i++) अणु
		lpm = 0x80 >> i;
		अगर ((cdev->निजी->pgid_valid_mask & lpm) == 0)
			जारी;
		pgid = &cdev->निजी->dma_area->pgid[i];
		अगर (sch->opm & lpm) अणु
			अगर (pgid->inf.ps.state1 != SNID_STATE1_GROUPED)
				जारी;
		पूर्ण अन्यथा अणु
			अगर (pgid->inf.ps.state1 != SNID_STATE1_UNGROUPED)
				जारी;
		पूर्ण
		अगर (cdev->निजी->flags.mpath) अणु
			अगर (pgid->inf.ps.state3 != SNID_STATE3_MULTI_PATH)
				जारी;
		पूर्ण अन्यथा अणु
			अगर (pgid->inf.ps.state3 != SNID_STATE3_SINGLE_PATH)
				जारी;
		पूर्ण
		करोnepm |= lpm;
	पूर्ण

	वापस करोnepm;
पूर्ण

अटल व्योम pgid_fill(काष्ठा ccw_device *cdev, काष्ठा pgid *pgid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		स_नकल(&cdev->निजी->dma_area->pgid[i], pgid,
		       माप(काष्ठा pgid));
पूर्ण

/*
 * Process SENSE PGID data and report result.
 */
अटल व्योम snid_करोne(काष्ठा ccw_device *cdev, पूर्णांक rc)
अणु
	काष्ठा ccw_dev_id *id = &cdev->निजी->dev_id;
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा pgid *pgid;
	पूर्णांक mismatch = 0;
	u8 reserved = 0;
	u8 reset = 0;
	u8 करोnepm;

	अगर (rc)
		जाओ out;
	pgid_analyze(cdev, &pgid, &mismatch, &reserved, &reset);
	अगर (reserved == cdev->निजी->pgid_valid_mask)
		rc = -EUSERS;
	अन्यथा अगर (mismatch)
		rc = -EOPNOTSUPP;
	अन्यथा अणु
		करोnepm = pgid_to_करोnepm(cdev);
		sch->vpm = करोnepm & sch->opm;
		cdev->निजी->pgid_reset_mask |= reset;
		cdev->निजी->pgid_toकरो_mask &=
			~(करोnepm | cdev->निजी->path_noirq_mask);
		pgid_fill(cdev, pgid);
	पूर्ण
out:
	CIO_MSG_EVENT(2, "snid: device 0.%x.%04x: rc=%d pvm=%02x vpm=%02x "
		      "todo=%02x mism=%d rsvd=%02x reset=%02x\n", id->ssid,
		      id->devno, rc, cdev->निजी->pgid_valid_mask, sch->vpm,
		      cdev->निजी->pgid_toकरो_mask, mismatch, reserved, reset);
	चयन (rc) अणु
	हाल 0:
		अगर (cdev->निजी->flags.pgid_unknown) अणु
			pgid_wipeout_start(cdev);
			वापस;
		पूर्ण
		/* Anything left to करो? */
		अगर (cdev->निजी->pgid_toकरो_mask == 0) अणु
			verअगरy_करोne(cdev, sch->vpm == 0 ? -EACCES : 0);
			वापस;
		पूर्ण
		/* Perक्रमm path-grouping. */
		spid_start(cdev);
		अवरोध;
	हाल -EOPNOTSUPP:
		/* Path-grouping not supported. */
		cdev->निजी->flags.pgroup = 0;
		cdev->निजी->flags.mpath = 0;
		verअगरy_start(cdev);
		अवरोध;
	शेष:
		verअगरy_करोne(cdev, rc);
	पूर्ण
पूर्ण

/*
 * Create channel program to perक्रमm a SENSE PGID on a single path.
 */
अटल व्योम snid_build_cp(काष्ठा ccw_device *cdev)
अणु
	काष्ठा ccw_request *req = &cdev->निजी->req;
	काष्ठा ccw1 *cp = cdev->निजी->dma_area->iccws;
	पूर्णांक i = pathmask_to_pos(req->lpm);

	/* Channel program setup. */
	cp->cmd_code	= CCW_CMD_SENSE_PGID;
	cp->cda		= (u32) (addr_t) &cdev->निजी->dma_area->pgid[i];
	cp->count	= माप(काष्ठा pgid);
	cp->flags	= CCW_FLAG_SLI;
	req->cp		= cp;
पूर्ण

/*
 * Perक्रमm SENSE PGID on a single path.
 */
अटल व्योम snid_करो(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा ccw_request *req = &cdev->निजी->req;
	पूर्णांक ret;

	req->lpm = lpm_adjust(req->lpm, sch->schib.pmcw.pam &
			      ~cdev->निजी->path_noirq_mask);
	अगर (!req->lpm)
		जाओ out_nopath;
	snid_build_cp(cdev);
	ccw_request_start(cdev);
	वापस;

out_nopath:
	अगर (cdev->निजी->pgid_valid_mask)
		ret = 0;
	अन्यथा अगर (cdev->निजी->path_noirq_mask)
		ret = -ETIME;
	अन्यथा
		ret = -EACCES;
	snid_करोne(cdev, ret);
पूर्ण

/*
 * Process SENSE PGID request result क्रम single path.
 */
अटल व्योम snid_callback(काष्ठा ccw_device *cdev, व्योम *data, पूर्णांक rc)
अणु
	काष्ठा ccw_request *req = &cdev->निजी->req;

	चयन (rc) अणु
	हाल 0:
		cdev->निजी->pgid_valid_mask |= req->lpm;
		अवरोध;
	हाल -ETIME:
		cdev->निजी->flags.pgid_unknown = 1;
		cdev->निजी->path_noirq_mask |= req->lpm;
		अवरोध;
	हाल -EACCES:
		cdev->निजी->path_notoper_mask |= req->lpm;
		अवरोध;
	शेष:
		जाओ err;
	पूर्ण
	/* Continue on the next path. */
	req->lpm >>= 1;
	snid_करो(cdev);
	वापस;

err:
	snid_करोne(cdev, rc);
पूर्ण

/*
 * Perक्रमm path verअगरication.
 */
अटल व्योम verअगरy_start(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा ccw_request *req = &cdev->निजी->req;
	काष्ठा ccw_dev_id *devid = &cdev->निजी->dev_id;

	sch->vpm = 0;
	sch->lpm = sch->schib.pmcw.pam;

	/* Initialize PGID data. */
	स_रखो(cdev->निजी->dma_area->pgid, 0,
	       माप(cdev->निजी->dma_area->pgid));
	cdev->निजी->pgid_valid_mask = 0;
	cdev->निजी->pgid_toकरो_mask = sch->schib.pmcw.pam;
	cdev->निजी->path_notoper_mask = 0;

	/* Initialize request data. */
	स_रखो(req, 0, माप(*req));
	req->समयout	= PGID_TIMEOUT;
	req->maxretries	= PGID_RETRIES;
	req->lpm	= 0x80;
	req->singlepath	= 1;
	अगर (cdev->निजी->flags.pgroup) अणु
		CIO_TRACE_EVENT(4, "snid");
		CIO_HEX_EVENT(4, devid, माप(*devid));
		req->callback	= snid_callback;
		snid_करो(cdev);
	पूर्ण अन्यथा अणु
		CIO_TRACE_EVENT(4, "nop");
		CIO_HEX_EVENT(4, devid, माप(*devid));
		req->filter	= nop_filter;
		req->callback	= nop_callback;
		nop_करो(cdev);
	पूर्ण
पूर्ण

/**
 * ccw_device_verअगरy_start - perक्रमm path verअगरication
 * @cdev: ccw device
 *
 * Perक्रमm an I/O on each available channel path to @cdev to determine which
 * paths are operational. The resulting path mask is stored in sch->vpm.
 * If device options specअगरy pathgrouping, establish a pathgroup क्रम the
 * operational paths. When finished, call ccw_device_verअगरy_करोne with a
 * वापस code specअगरying the result.
 */
व्योम ccw_device_verअगरy_start(काष्ठा ccw_device *cdev)
अणु
	CIO_TRACE_EVENT(4, "vrfy");
	CIO_HEX_EVENT(4, &cdev->निजी->dev_id, माप(cdev->निजी->dev_id));
	/*
	 * Initialize pathgroup and multipath state with target values.
	 * They may change in the course of path verअगरication.
	 */
	cdev->निजी->flags.pgroup = cdev->निजी->options.pgroup;
	cdev->निजी->flags.mpath = cdev->निजी->options.mpath;
	cdev->निजी->flags.करोverअगरy = 0;
	cdev->निजी->path_noirq_mask = 0;
	verअगरy_start(cdev);
पूर्ण

/*
 * Process disband SET PGID request result.
 */
अटल व्योम disband_callback(काष्ठा ccw_device *cdev, व्योम *data, पूर्णांक rc)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा ccw_dev_id *id = &cdev->निजी->dev_id;

	अगर (rc)
		जाओ out;
	/* Ensure consistent multipathing state at device and channel. */
	cdev->निजी->flags.mpath = 0;
	अगर (sch->config.mp) अणु
		sch->config.mp = 0;
		rc = cio_commit_config(sch);
	पूर्ण
out:
	CIO_MSG_EVENT(0, "disb: device 0.%x.%04x: rc=%d\n", id->ssid, id->devno,
		      rc);
	ccw_device_disband_करोne(cdev, rc);
पूर्ण

/**
 * ccw_device_disband_start - disband pathgroup
 * @cdev: ccw device
 *
 * Execute a SET PGID channel program on @cdev to disband a previously
 * established pathgroup. When finished, call ccw_device_disband_करोne with
 * a वापस code specअगरying the result.
 */
व्योम ccw_device_disband_start(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा ccw_request *req = &cdev->निजी->req;
	u8 fn;

	CIO_TRACE_EVENT(4, "disb");
	CIO_HEX_EVENT(4, &cdev->निजी->dev_id, माप(cdev->निजी->dev_id));
	/* Request setup. */
	स_रखो(req, 0, माप(*req));
	req->समयout	= PGID_TIMEOUT;
	req->maxretries	= PGID_RETRIES;
	req->lpm	= sch->schib.pmcw.pam & sch->opm;
	req->singlepath	= 1;
	req->callback	= disband_callback;
	fn = SPID_FUNC_DISBAND;
	अगर (cdev->निजी->flags.mpath)
		fn |= SPID_FUNC_MULTI_PATH;
	spid_build_cp(cdev, fn);
	ccw_request_start(cdev);
पूर्ण

काष्ठा stlck_data अणु
	काष्ठा completion करोne;
	पूर्णांक rc;
पूर्ण;

अटल व्योम stlck_build_cp(काष्ठा ccw_device *cdev, व्योम *buf1, व्योम *buf2)
अणु
	काष्ठा ccw_request *req = &cdev->निजी->req;
	काष्ठा ccw1 *cp = cdev->निजी->dma_area->iccws;

	cp[0].cmd_code = CCW_CMD_STLCK;
	cp[0].cda = (u32) (addr_t) buf1;
	cp[0].count = 32;
	cp[0].flags = CCW_FLAG_CC;
	cp[1].cmd_code = CCW_CMD_RELEASE;
	cp[1].cda = (u32) (addr_t) buf2;
	cp[1].count = 32;
	cp[1].flags = 0;
	req->cp = cp;
पूर्ण

अटल व्योम stlck_callback(काष्ठा ccw_device *cdev, व्योम *data, पूर्णांक rc)
अणु
	काष्ठा stlck_data *sdata = data;

	sdata->rc = rc;
	complete(&sdata->करोne);
पूर्ण

/**
 * ccw_device_stlck_start - perक्रमm unconditional release
 * @cdev: ccw device
 * @data: data poपूर्णांकer to be passed to ccw_device_stlck_करोne
 * @buf1: data poपूर्णांकer used in channel program
 * @buf2: data poपूर्णांकer used in channel program
 *
 * Execute a channel program on @cdev to release an existing PGID reservation.
 */
अटल व्योम ccw_device_stlck_start(काष्ठा ccw_device *cdev, व्योम *data,
				   व्योम *buf1, व्योम *buf2)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा ccw_request *req = &cdev->निजी->req;

	CIO_TRACE_EVENT(4, "stlck");
	CIO_HEX_EVENT(4, &cdev->निजी->dev_id, माप(cdev->निजी->dev_id));
	/* Request setup. */
	स_रखो(req, 0, माप(*req));
	req->समयout	= PGID_TIMEOUT;
	req->maxretries	= PGID_RETRIES;
	req->lpm	= sch->schib.pmcw.pam & sch->opm;
	req->data	= data;
	req->callback	= stlck_callback;
	stlck_build_cp(cdev, buf1, buf2);
	ccw_request_start(cdev);
पूर्ण

/*
 * Perक्रमm unconditional reserve + release.
 */
पूर्णांक ccw_device_stlck(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा stlck_data data;
	u8 *buffer;
	पूर्णांक rc;

	/* Check अगर steal lock operation is valid क्रम this device. */
	अगर (cdev->drv) अणु
		अगर (!cdev->निजी->options.क्रमce)
			वापस -EINVAL;
	पूर्ण
	buffer = kzalloc(64, GFP_DMA | GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;
	init_completion(&data.करोne);
	data.rc = -EIO;
	spin_lock_irq(sch->lock);
	rc = cio_enable_subchannel(sch, (u32) (addr_t) sch);
	अगर (rc)
		जाओ out_unlock;
	/* Perक्रमm operation. */
	cdev->निजी->state = DEV_STATE_STEAL_LOCK;
	ccw_device_stlck_start(cdev, &data, &buffer[0], &buffer[32]);
	spin_unlock_irq(sch->lock);
	/* Wait क्रम operation to finish. */
	अगर (रुको_क्रम_completion_पूर्णांकerruptible(&data.करोne)) अणु
		/* Got a संकेत. */
		spin_lock_irq(sch->lock);
		ccw_request_cancel(cdev);
		spin_unlock_irq(sch->lock);
		रुको_क्रम_completion(&data.करोne);
	पूर्ण
	rc = data.rc;
	/* Check results. */
	spin_lock_irq(sch->lock);
	cio_disable_subchannel(sch);
	cdev->निजी->state = DEV_STATE_BOXED;
out_unlock:
	spin_unlock_irq(sch->lock);
	kमुक्त(buffer);

	वापस rc;
पूर्ण
