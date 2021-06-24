<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2008 Cavium Networks
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this file; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a dअगरferent license from Cavium.
 * Contact Cavium Networks क्रम more inक्रमmation
 ***********************license end**************************************/

/*
 *
 * This file contains defines क्रम the SPI पूर्णांकerface
 */
#अगर_अघोषित __CVMX_SPI_H__
#घोषणा __CVMX_SPI_H__

#समावेश <यंत्र/octeon/cvmx-gmxx-defs.h>

/* CSR प्रकारs have been moved to cvmx-csr-*.h */

प्रकार क्रमागत अणु
	CVMX_SPI_MODE_UNKNOWN = 0,
	CVMX_SPI_MODE_TX_HALFPLEX = 1,
	CVMX_SPI_MODE_RX_HALFPLEX = 2,
	CVMX_SPI_MODE_DUPLEX = 3
पूर्ण cvmx_spi_mode_t;

/** Callbacks काष्ठाure to customize SPI4 initialization sequence */
प्रकार काष्ठा अणु
    /** Called to reset SPI4 DLL */
	पूर्णांक (*reset_cb) (पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode);

    /** Called to setup calendar */
	पूर्णांक (*calendar_setup_cb) (पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode,
				  पूर्णांक num_ports);

    /** Called क्रम Tx and Rx घड़ी detection */
	पूर्णांक (*घड़ी_detect_cb) (पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode,
				पूर्णांक समयout);

    /** Called to perक्रमm link training */
	पूर्णांक (*training_cb) (पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode, पूर्णांक समयout);

    /** Called क्रम calendar data synchronization */
	पूर्णांक (*calendar_sync_cb) (पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode,
				 पूर्णांक समयout);

    /** Called when पूर्णांकerface is up */
	पूर्णांक (*पूर्णांकerface_up_cb) (पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode);

पूर्ण cvmx_spi_callbacks_t;

/**
 * Return true अगर the supplied पूर्णांकerface is configured क्रम SPI
 *
 * @पूर्णांकerface: Interface to check
 * Returns True अगर पूर्णांकerface is SPI
 */
अटल अंतरभूत पूर्णांक cvmx_spi_is_spi_पूर्णांकerface(पूर्णांक पूर्णांकerface)
अणु
	uपूर्णांक64_t gmxState = cvmx_पढ़ो_csr(CVMX_GMXX_INF_MODE(पूर्णांकerface));
	वापस (gmxState & 0x2) && (gmxState & 0x1);
पूर्ण

/**
 * Initialize and start the SPI पूर्णांकerface.
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 * @समयout:   Timeout to रुको क्रम घड़ी synchronization in seconds
 * @num_ports: Number of SPI ports to configure
 *
 * Returns Zero on success, negative of failure.
 */
बाह्य पूर्णांक cvmx_spi_start_पूर्णांकerface(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode,
				    पूर्णांक समयout, पूर्णांक num_ports);

/**
 * This routine restarts the SPI पूर्णांकerface after it has lost synchronization
 * with its corespondant प्रणाली.
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 * @समयout:   Timeout to रुको क्रम घड़ी synchronization in seconds
 * Returns Zero on success, negative of failure.
 */
बाह्य पूर्णांक cvmx_spi_restart_पूर्णांकerface(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode,
				      पूर्णांक समयout);

/**
 * Return non-zero अगर the SPI पूर्णांकerface has a SPI4000 attached
 *
 * @पूर्णांकerface: SPI पूर्णांकerface the SPI4000 is connected to
 *
 * Returns
 */
अटल अंतरभूत पूर्णांक cvmx_spi4000_is_present(पूर्णांक पूर्णांकerface)
अणु
	वापस 0;
पूर्ण

/**
 * Initialize the SPI4000 क्रम use
 *
 * @पूर्णांकerface: SPI पूर्णांकerface the SPI4000 is connected to
 */
अटल अंतरभूत पूर्णांक cvmx_spi4000_initialize(पूर्णांक पूर्णांकerface)
अणु
	वापस 0;
पूर्ण

/**
 * Poll all the SPI4000 port and check its speed
 *
 * @पूर्णांकerface: Interface the SPI4000 is on
 * @port:      Port to poll (0-9)
 * Returns Status of the port. 0=करोwn. All other values the port is up.
 */
अटल अंतरभूत जोड़ cvmx_gmxx_rxx_rx_inbnd cvmx_spi4000_check_speed(
	पूर्णांक पूर्णांकerface,
	पूर्णांक port)
अणु
	जोड़ cvmx_gmxx_rxx_rx_inbnd r;
	r.u64 = 0;
	वापस r;
पूर्ण

/**
 * Get current SPI4 initialization callbacks
 *
 * @callbacks:	Poपूर्णांकer to the callbacks काष्ठाure.to fill
 *
 * Returns Poपूर्णांकer to cvmx_spi_callbacks_t काष्ठाure.
 */
बाह्य व्योम cvmx_spi_get_callbacks(cvmx_spi_callbacks_t *callbacks);

/**
 * Set new SPI4 initialization callbacks
 *
 * @new_callbacks:  Poपूर्णांकer to an updated callbacks काष्ठाure.
 */
बाह्य व्योम cvmx_spi_set_callbacks(cvmx_spi_callbacks_t *new_callbacks);

/**
 * Callback to perक्रमm SPI4 reset
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 *
 * Returns Zero on success, non-zero error code on failure (will cause
 * SPI initialization to पात)
 */
बाह्य पूर्णांक cvmx_spi_reset_cb(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode);

/**
 * Callback to setup calendar and miscellaneous settings beक्रमe घड़ी
 * detection
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 * @num_ports: Number of ports to configure on SPI
 *
 * Returns Zero on success, non-zero error code on failure (will cause
 * SPI initialization to पात)
 */
बाह्य पूर्णांक cvmx_spi_calendar_setup_cb(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode,
				      पूर्णांक num_ports);

/**
 * Callback to perक्रमm घड़ी detection
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 * @समयout:   Timeout to रुको क्रम घड़ी synchronization in seconds
 *
 * Returns Zero on success, non-zero error code on failure (will cause
 * SPI initialization to पात)
 */
बाह्य पूर्णांक cvmx_spi_घड़ी_detect_cb(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode,
				    पूर्णांक समयout);

/**
 * Callback to perक्रमm link training
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 * @समयout:   Timeout to रुको क्रम link to be trained (in seconds)
 *
 * Returns Zero on success, non-zero error code on failure (will cause
 * SPI initialization to पात)
 */
बाह्य पूर्णांक cvmx_spi_training_cb(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode,
				पूर्णांक समयout);

/**
 * Callback to perक्रमm calendar data synchronization
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 * @समयout:   Timeout to रुको क्रम calendar data in seconds
 *
 * Returns Zero on success, non-zero error code on failure (will cause
 * SPI initialization to पात)
 */
बाह्य पूर्णांक cvmx_spi_calendar_sync_cb(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode,
				     पूर्णांक समयout);

/**
 * Callback to handle पूर्णांकerface up
 *
 * @पूर्णांकerface: The identअगरier of the packet पूर्णांकerface to configure and
 *		    use as a SPI पूर्णांकerface.
 * @mode:      The operating mode क्रम the SPI पूर्णांकerface. The पूर्णांकerface
 *		    can operate as a full duplex (both Tx and Rx data paths
 *		    active) or as a halfplex (either the Tx data path is
 *		    active or the Rx data path is active, but not both).
 *
 * Returns Zero on success, non-zero error code on failure (will cause
 * SPI initialization to पात)
 */
बाह्य पूर्णांक cvmx_spi_पूर्णांकerface_up_cb(पूर्णांक पूर्णांकerface, cvmx_spi_mode_t mode);

#पूर्ण_अगर /* __CVMX_SPI_H__ */
