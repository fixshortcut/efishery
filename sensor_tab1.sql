-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Waktu pembuatan: 02 Okt 2022 pada 13.48
-- Versi server: 10.4.24-MariaDB
-- Versi PHP: 8.0.19

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `sensor_logger`
--

-- --------------------------------------------------------

--
-- Struktur dari tabel `sensor_tab1`
--

CREATE TABLE `sensor_tab1` (
  `NO` int(11) NOT NULL,
  `time_stamp` timestamp(6) NOT NULL DEFAULT current_timestamp(6),
  `sensor1_data` int(11) NOT NULL,
  `sensor2_data` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data untuk tabel `sensor_tab1`
--

INSERT INTO `sensor_tab1` (`NO`, `time_stamp`, `sensor1_data`, `sensor2_data`) VALUES
(1, '2022-10-02 09:39:42.419144', 66, 28),
(2, '2022-10-02 09:40:47.743768', 11, 28),
(3, '2022-10-02 10:12:36.377867', 36, 13),
(4, '2022-10-02 10:13:30.851025', 46, 23),
(5, '2022-10-02 10:13:48.461609', 29, 25);

--
-- Indexes for dumped tables
--

--
-- Indeks untuk tabel `sensor_tab1`
--
ALTER TABLE `sensor_tab1`
  ADD PRIMARY KEY (`NO`);

--
-- AUTO_INCREMENT untuk tabel yang dibuang
--

--
-- AUTO_INCREMENT untuk tabel `sensor_tab1`
--
ALTER TABLE `sensor_tab1`
  MODIFY `NO` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
