-- phpMyAdmin SQL Dump
-- version 4.0.10
-- http://www.phpmyadmin.net
--
-- Хост: 127.0.0.1:3306
-- Время создания: Авг 18 2014 г., 00:04
-- Версия сервера: 5.5.38-log
-- Версия PHP: 5.4.29

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- База данных: `StudBd1`
--

-- --------------------------------------------------------

--
-- Структура таблицы `Departments`
--

CREATE TABLE IF NOT EXISTS `Departments` (
  `id` int(11) NOT NULL,
  `nameOfDepartment` varchar(50) NOT NULL,
  `Adress` varchar(50) NOT NULL,
  `Telephone` varchar(50) NOT NULL,
  `idForTeacher` int(11) NOT NULL,
  `IdForFaculties` int(11) DEFAULT NULL,
  `idForInstitutes` int(11) DEFAULT NULL,
  KEY `Индекс 1` (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `Departments`
--

INSERT INTO `Departments` (`id`, `nameOfDepartment`, `Adress`, `Telephone`, `idForTeacher`, `IdForFaculties`, `idForInstitutes`) VALUES
(1, 'Математики і механіки', '', '', 1, 1, NULL),
(2, 'Прикладної математики та інформаційних комп''ютерни', '', '', 1, 1, NULL),
(3, 'Комп''ютерних систем та мереж', '', '', 0, 1, NULL),
(4, 'Фізики', '', '', 0, 1, NULL),
(5, 'Української мови та лінгводидактики', '', '', 0, 2, NULL),
(6, 'Української літератури та методики навчання', '', '', 0, 2, NULL),
(7, 'Мовознавства та логопедії', '', '', 0, 2, NULL),
(8, 'Слов''янської філології', '', '', 0, 2, NULL),
(9, 'Біології людини та тварин', '', '', 0, 3, NULL),
(10, 'Фізіології та біохімії', '', '', 0, 3, NULL),
(11, 'Ботаніки', '', '', 0, 3, NULL),
(12, 'Екології та здоров''я людини', '', '', 0, 3, NULL),
(13, 'Теорії і методики фізичного виховання та біології ', '', '', 0, NULL, 1),
(14, 'Спортивних дисциплін', '', '', 0, NULL, 1),
(15, 'Фізичного виховання', '', '', 0, NULL, 1),
(16, 'Спортивних ігор та гімнастики', '', '', 0, NULL, 1),
(17, 'Військової підготовки', '', '', 0, NULL, 1),
(18, 'Історії України', '', '', 0, NULL, 2),
(19, 'Археології, давньої та середньовічної історії', '', '', 0, NULL, 2),
(20, 'Правознавства', '', '', 0, NULL, 2),
(21, 'Політології', '', '', 0, NULL, 2),
(22, 'Педагогіки та методики викладання суспільствознавч', '', '', 0, NULL, 2),
(23, 'Нової та новітньої історії', '', '', 0, NULL, 2),
(24, 'Методики початкової освіти', '', '', 0, NULL, 3),
(25, 'Педагогіки початкової освіти', '', '', 0, NULL, 3),
(26, 'Педагогіки', '', '', 0, NULL, 3),
(27, 'Філософії', '', '', 0, NULL, 3),
(28, 'Музичного мистецтва', '', '', 0, NULL, 3),
(29, 'Дошкільної освіти і соціального розвитку дитини', '', '', 0, 4, NULL),
(30, 'Теорії та методики виховання і психологічного розв', '', '', 0, 4, NULL),
(31, 'Філософської думки та культурології', '', '', 0, 4, NULL),
(32, 'Англійської філології', '', '', 0, 5, NULL),
(33, 'Перекладу та німецької філології', '', '', 0, 5, NULL),
(34, 'Перекладознавства', '', '', 0, 5, NULL),
(35, 'Іноземних мов', '', '', 0, 5, NULL),
(36, 'Соціальної психології та управління', '', '', 0, 6, NULL),
(37, 'Теоретичної та прикладної психології', '', '', 0, 6, NULL),
(38, 'Соціальної педагогіки', '', '', 0, 6, NULL),
(39, 'Соціальної роботи', '', '', 0, 6, NULL),
(40, 'Загальної та вікової психології', '', '', 0, 6, NULL),
(41, 'Обліку і фінансів', '', '', 0, 7, NULL),
(42, 'Міжнародної економіки та економічної теорії', '', '', 0, 7, NULL),
(43, 'Економіки та менеджменту', '', '', 0, 7, NULL),
(44, 'Фінансів та кредиту', '', '', 0, 7, NULL);

-- --------------------------------------------------------

--
-- Структура таблицы `FacultatesAndInstitutes`
--

CREATE TABLE IF NOT EXISTS `FacultatesAndInstitutes` (
  `id` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `Faculties`
--

CREATE TABLE IF NOT EXISTS `Faculties` (
  `id` int(11) NOT NULL,
  `NameOfFaculties` varchar(100) DEFAULT NULL,
  `Adress` varchar(100) DEFAULT NULL,
  `Tel` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `Faculties`
--

INSERT INTO `Faculties` (`id`, `NameOfFaculties`, `Adress`, `Tel`) VALUES
(1, 'Механіко - математичний факультет', 'навчальний корпус №2, вул. Нікольська, 24, м. Миколаїв', '(0512) 37-88-12'),
(2, 'Факультет філології та журналістики', '54030, м. Миколаїв, вул. Нікольська, 24.', '(0512) 37-88-32'),
(3, 'Біологічний факультет', 'вул. Морехідна, 2А (навчальний корпус №11)', '(0512) 76-98-22'),
(4, 'Факультет розвитку дитини', 'вул. Нікольська, 24, м. Миколаїв, 54030', '(0512) 37-88-29'),
(5, 'Факультет іноземної філології', 'навчальний корпус №21, вул. Нікольська, 24, м. Миколаїв', '(0512) 37-88-07'),
(6, 'Факультет психології', 'вул. Маршала Василевського, 55-Б, м. Миколаїв', '(0512) 55-57-10'),
(7, 'Факультет економіки', 'навчальний корпус №2, вул. Нікольська, 24, м. Миколаїв', '(0512) 76-76-21');

-- --------------------------------------------------------

--
-- Структура таблицы `Institutes`
--

CREATE TABLE IF NOT EXISTS `Institutes` (
  `id` int(11) NOT NULL,
  `NameOfInstitut` varchar(50) NOT NULL,
  `Adress` varchar(50) NOT NULL,
  `Tel` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `Institutes`
--

INSERT INTO `Institutes` (`id`, `NameOfInstitut`, `Adress`, `Tel`) VALUES
(1, 'Інститут фізичної культури та спорту', 'корпус №4, вул. Нікольська, 24, Миколаїв', '(0512) 37-88-03'),
(2, 'Інститут історії та права', 'пл. Комунарів, 1, м. Миколаїв, 54003', '(0512) 24-50-94'),
(3, 'Інститут педагогічної оствіти', 'навчальний корпус № 21, вул. Нікольська 24, м. Мик', '(0512) 37-89-53 ');

-- --------------------------------------------------------

--
-- Структура таблицы `LigingActions`
--

CREATE TABLE IF NOT EXISTS `LigingActions` (
  `id` int(11) NOT NULL,
  `login` varchar(50) DEFAULT NULL,
  `accesslevl` varchar(50) DEFAULT NULL,
  `datatime` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `LigingActions`
--

INSERT INTO `LigingActions` (`id`, `login`, `accesslevl`, `datatime`) VALUES
(0, 'admin', 'superuser', '22.16.28-15.08.2014'),
(1, 'admin', 'superuser', '22.17.02-15.08.2014'),
(2, 'admin', 'superuser', '22:17:32-15.08.2014'),
(3, 'admin', 'superuser', '00:41:37-16.08.2014'),
(4, 'admin', 'superuser', '00:42:10-16.08.2014'),
(5, 'admin', 'superuser', '00:43:15-16.08.2014'),
(6, 'admin', 'superuser', '00:47:27-16.08.2014'),
(7, 'admin', 'superuser', '00:49:12-16.08.2014'),
(8, 'admin', 'superuser', '00:54:21-16.08.2014'),
(9, 'admin', 'superuser', '00:56:36-16.08.2014'),
(10, 'admin', 'superuser', '00:58:57-16.08.2014'),
(11, 'admin', 'superuser', '01:00:47-16.08.2014'),
(12, 'admin', 'superuser', '01:01:35-16.08.2014'),
(13, 'admin', 'superuser', '01:02:05-16.08.2014'),
(14, 'admin', 'superuser', '01:02:19-16.08.2014'),
(15, 'admin', 'superuser', '01:04:03-16.08.2014'),
(16, 'admin', 'superuser', '01:08:11-16.08.2014'),
(17, 'admin', 'superuser', '01:10:57-16.08.2014'),
(18, 'admin', 'superuser', '01:11:32-16.08.2014'),
(19, 'admin', 'superuser', '01:11:55-16.08.2014'),
(20, 'admin', 'superuser', '01:22:45-16.08.2014'),
(21, 'admin', 'superuser', '12:19:15-16.08.2014'),
(22, 'admin', 'superuser', '11:45:23-17.08.2014'),
(23, 'admin', 'superuser', '11:59:48-17.08.2014'),
(24, 'admin', 'superuser', '12:20:12-17.08.2014'),
(25, 'admin', 'superuser', '12:22:05-17.08.2014'),
(26, 'admin', 'superuser', '12:22:47-17.08.2014'),
(27, 'admin', 'superuser', '12:23:07-17.08.2014');

-- --------------------------------------------------------

--
-- Структура таблицы `Students`
--

CREATE TABLE IF NOT EXISTS `Students` (
  `id` int(11) NOT NULL,
  `NameOfStudent` varchar(50) NOT NULL,
  `DateOfBirth` varchar(50) NOT NULL,
  `Telephone` varchar(50) NOT NULL,
  `DateOfEntry` varchar(50) NOT NULL,
  `EndDate` varchar(50) NOT NULL,
  `Shcool` varchar(50) NOT NULL,
  `FatherName` varchar(50) NOT NULL,
  `MotherName` varchar(50) NOT NULL,
  `ParentsPhone` varchar(50) NOT NULL,
  `Benefits` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `Teachers`
--

CREATE TABLE IF NOT EXISTS `Teachers` (
  `id` int(11) DEFAULT NULL,
  `NameOfTeacher` varchar(50) DEFAULT NULL,
  `Telephone` varchar(50) DEFAULT NULL,
  `idForDirection` varchar(50) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `Users`
--

CREATE TABLE IF NOT EXISTS `Users` (
  `id` int(11) NOT NULL,
  `login` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL,
  `accesslevel` varchar(10) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id` (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `Users`
--

INSERT INTO `Users` (`id`, `login`, `password`, `accesslevel`) VALUES
(0, 'admin', 'admin', 'superuser'),
(1, 'administrator', '12345', 'admin'),
(2, 'sdg', '234', 'reg'),
(3, '''sdg''', '''sfg''', '''reg'''),
(4, 'sdg', 'sdfg', 'reg'),
(5, 'sfg', 'sdfh', 'reg'),
(6, '123434', 'sdfgfdgdfg', 'reg'),
(7, '2', '32', 'reg');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
