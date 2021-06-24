<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* 
 *  Parallel SCSI (SPI) transport specअगरic attributes exported to sysfs.
 *
 *  Copyright (c) 2003 Silicon Graphics, Inc.  All rights reserved.
 */
#अगर_अघोषित SCSI_TRANSPORT_SPI_H
#घोषणा SCSI_TRANSPORT_SPI_H

#समावेश <linux/transport_class.h>
#समावेश <linux/mutex.h>

काष्ठा scsi_transport_ढाँचा;
काष्ठा scsi_target;
काष्ठा scsi_device;
काष्ठा Scsi_Host;

काष्ठा spi_transport_attrs अणु
	पूर्णांक period;		/* value in the PPR/SDTR command */
	पूर्णांक min_period;
	पूर्णांक offset;
	पूर्णांक max_offset;
	अचिन्हित पूर्णांक width:1;	/* 0 - narrow, 1 - wide */
	अचिन्हित पूर्णांक max_width:1;
	अचिन्हित पूर्णांक iu:1;	/* Inक्रमmation Units enabled */
	अचिन्हित पूर्णांक max_iu:1;
	अचिन्हित पूर्णांक dt:1;	/* DT घड़ीing enabled */
	अचिन्हित पूर्णांक qas:1;	/* Quick Arbitration and Selection enabled */
	अचिन्हित पूर्णांक max_qas:1;
	अचिन्हित पूर्णांक wr_flow:1;	/* Write Flow control enabled */
	अचिन्हित पूर्णांक rd_strm:1;	/* Read streaming enabled */
	अचिन्हित पूर्णांक rti:1;	/* Retain Training Inक्रमmation */
	अचिन्हित पूर्णांक pcomp_en:1;/* Precompensation enabled */
	अचिन्हित पूर्णांक hold_mcs:1;/* Hold Margin Control Settings */
	अचिन्हित पूर्णांक initial_dv:1; /* DV करोne to this target yet  */
	अचिन्हित दीर्घ flags;	/* flags field क्रम drivers to use */
	/* Device Properties fields */
	अचिन्हित पूर्णांक support_sync:1; /* synchronous support */
	अचिन्हित पूर्णांक support_wide:1; /* wide support */
	अचिन्हित पूर्णांक support_dt:1; /* allows DT phases */
	अचिन्हित पूर्णांक support_dt_only; /* disallows ST phases */
	अचिन्हित पूर्णांक support_ius; /* support Inक्रमmation Units */
	अचिन्हित पूर्णांक support_qas; /* supports quick arbitration and selection */
	/* Private Fields */
	अचिन्हित पूर्णांक dv_pending:1; /* Internal flag: DV Requested */
	अचिन्हित पूर्णांक dv_in_progress:1;	/* Internal: DV started */
	काष्ठा mutex dv_mutex; /* semaphore to serialise dv */
पूर्ण;

क्रमागत spi_संकेत_type अणु
	SPI_SIGNAL_UNKNOWN = 1,
	SPI_SIGNAL_SE,
	SPI_SIGNAL_LVD,
	SPI_SIGNAL_HVD,
पूर्ण;

काष्ठा spi_host_attrs अणु
	क्रमागत spi_संकेत_type संकेतling;
पूर्ण;

/* accessor functions */
#घोषणा spi_period(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->period)
#घोषणा spi_min_period(x) (((काष्ठा spi_transport_attrs *)&(x)->starget_data)->min_period)
#घोषणा spi_offset(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->offset)
#घोषणा spi_max_offset(x) (((काष्ठा spi_transport_attrs *)&(x)->starget_data)->max_offset)
#घोषणा spi_width(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->width)
#घोषणा spi_max_width(x) (((काष्ठा spi_transport_attrs *)&(x)->starget_data)->max_width)
#घोषणा spi_iu(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->iu)
#घोषणा spi_max_iu(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->max_iu)
#घोषणा spi_dt(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->dt)
#घोषणा spi_qas(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->qas)
#घोषणा spi_max_qas(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->max_qas)
#घोषणा spi_wr_flow(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->wr_flow)
#घोषणा spi_rd_strm(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->rd_strm)
#घोषणा spi_rti(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->rti)
#घोषणा spi_pcomp_en(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->pcomp_en)
#घोषणा spi_hold_mcs(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->hold_mcs)
#घोषणा spi_initial_dv(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->initial_dv)
#घोषणा spi_dv_pending(x) (((काष्ठा spi_transport_attrs *)&(x)->starget_data)->dv_pending)

#घोषणा spi_support_sync(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->support_sync)
#घोषणा spi_support_wide(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->support_wide)
#घोषणा spi_support_dt(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->support_dt)
#घोषणा spi_support_dt_only(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->support_dt_only)
#घोषणा spi_support_ius(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->support_ius)
#घोषणा spi_support_qas(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->support_qas)

#घोषणा spi_flags(x)	(((काष्ठा spi_transport_attrs *)&(x)->starget_data)->flags)
#घोषणा spi_संकेतling(h)	(((काष्ठा spi_host_attrs *)(h)->shost_data)->संकेतling)



/* The functions by which the transport class and the driver communicate */
काष्ठा spi_function_ढाँचा अणु
	व्योम	(*get_period)(काष्ठा scsi_target *);
	व्योम	(*set_period)(काष्ठा scsi_target *, पूर्णांक);
	व्योम	(*get_offset)(काष्ठा scsi_target *);
	व्योम	(*set_offset)(काष्ठा scsi_target *, पूर्णांक);
	व्योम	(*get_width)(काष्ठा scsi_target *);
	व्योम	(*set_width)(काष्ठा scsi_target *, पूर्णांक);
	व्योम	(*get_iu)(काष्ठा scsi_target *);
	व्योम	(*set_iu)(काष्ठा scsi_target *, पूर्णांक);
	व्योम	(*get_dt)(काष्ठा scsi_target *);
	व्योम	(*set_dt)(काष्ठा scsi_target *, पूर्णांक);
	व्योम	(*get_qas)(काष्ठा scsi_target *);
	व्योम	(*set_qas)(काष्ठा scsi_target *, पूर्णांक);
	व्योम	(*get_wr_flow)(काष्ठा scsi_target *);
	व्योम	(*set_wr_flow)(काष्ठा scsi_target *, पूर्णांक);
	व्योम	(*get_rd_strm)(काष्ठा scsi_target *);
	व्योम	(*set_rd_strm)(काष्ठा scsi_target *, पूर्णांक);
	व्योम	(*get_rti)(काष्ठा scsi_target *);
	व्योम	(*set_rti)(काष्ठा scsi_target *, पूर्णांक);
	व्योम	(*get_pcomp_en)(काष्ठा scsi_target *);
	व्योम	(*set_pcomp_en)(काष्ठा scsi_target *, पूर्णांक);
	व्योम	(*get_hold_mcs)(काष्ठा scsi_target *);
	व्योम	(*set_hold_mcs)(काष्ठा scsi_target *, पूर्णांक);
	व्योम	(*get_संकेतling)(काष्ठा Scsi_Host *);
	व्योम	(*set_संकेतling)(काष्ठा Scsi_Host *, क्रमागत spi_संकेत_type);
	पूर्णांक	(*deny_binding)(काष्ठा scsi_target *);
	/* The driver sets these to tell the transport class it
	 * wants the attributes displayed in sysfs.  If the show_ flag
	 * is not set, the attribute will be निजी to the transport
	 * class */
	अचिन्हित दीर्घ	show_period:1;
	अचिन्हित दीर्घ	show_offset:1;
	अचिन्हित दीर्घ	show_width:1;
	अचिन्हित दीर्घ	show_iu:1;
	अचिन्हित दीर्घ	show_dt:1;
	अचिन्हित दीर्घ	show_qas:1;
	अचिन्हित दीर्घ	show_wr_flow:1;
	अचिन्हित दीर्घ	show_rd_strm:1;
	अचिन्हित दीर्घ	show_rti:1;
	अचिन्हित दीर्घ	show_pcomp_en:1;
	अचिन्हित दीर्घ	show_hold_mcs:1;
पूर्ण;

काष्ठा scsi_transport_ढाँचा *spi_attach_transport(काष्ठा spi_function_ढाँचा *);
व्योम spi_release_transport(काष्ठा scsi_transport_ढाँचा *);
व्योम spi_schedule_dv_device(काष्ठा scsi_device *);
व्योम spi_dv_device(काष्ठा scsi_device *);
व्योम spi_display_xfer_agreement(काष्ठा scsi_target *);
पूर्णांक spi_prपूर्णांक_msg(स्थिर अचिन्हित अक्षर *);
पूर्णांक spi_populate_width_msg(अचिन्हित अक्षर *msg, पूर्णांक width);
पूर्णांक spi_populate_sync_msg(अचिन्हित अक्षर *msg, पूर्णांक period, पूर्णांक offset);
पूर्णांक spi_populate_ppr_msg(अचिन्हित अक्षर *msg, पूर्णांक period, पूर्णांक offset, पूर्णांक width,
		पूर्णांक options);
पूर्णांक spi_populate_tag_msg(अचिन्हित अक्षर *msg, काष्ठा scsi_cmnd *cmd);

#पूर्ण_अगर /* SCSI_TRANSPORT_SPI_H */
