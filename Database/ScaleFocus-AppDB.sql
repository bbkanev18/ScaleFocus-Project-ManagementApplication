USE [master]
GO
/****** Object:  Database [ScaleFocus-AppDB]    Script Date: 7/12/2021 2:46:56 PM ******/
CREATE DATABASE [ScaleFocus-AppDB]
 CONTAINMENT = NONE
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [ScaleFocus-AppDB].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [ScaleFocus-AppDB] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET ARITHABORT OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET  DISABLE_BROKER 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET RECOVERY SIMPLE 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET  MULTI_USER 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [ScaleFocus-AppDB] SET DB_CHAINING OFF 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [ScaleFocus-AppDB] SET DELAYED_DURABILITY = DISABLED 
GO
USE [ScaleFocus-AppDB]
GO
/****** Object:  Table [dbo].[Projects]    Script Date: 7/12/2021 2:46:56 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Projects](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Title] [nvarchar](255) NOT NULL,
	[Description] [nvarchar](255) NOT NULL,
	[DateOfCreation] [datetime] NOT NULL,
	[IdOfCreator] [int] NOT NULL,
	[DateOfLastChange] [datetime] NOT NULL,
	[IdOfUserLastChange] [int] NOT NULL,
	[IdTeam] [int] NOT NULL,
	[IsDeleted] [int] NOT NULL,
 CONSTRAINT [PK_Project] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Tasks]    Script Date: 7/12/2021 2:46:56 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Tasks](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[IdOfProject] [int] NOT NULL,
	[IdOfAssignee] [int] NOT NULL,
	[Title] [nvarchar](255) NOT NULL,
	[Description] [nvarchar](255) NOT NULL,
	[Status] [int] NOT NULL,
	[DateOfCreation] [datetime] NOT NULL,
	[IdOfCreator] [int] NOT NULL,
	[DateOfLastChange] [datetime] NOT NULL,
	[IdOfTheUserLastChange] [int] NOT NULL,
	[IsDeleted] [int] NOT NULL,
 CONSTRAINT [PK_Task] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Teams]    Script Date: 7/12/2021 2:46:56 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Teams](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Title] [nvarchar](255) NOT NULL,
	[DateOfCreation] [datetime] NOT NULL,
	[IdOfCreator] [int] NOT NULL,
	[DateOfLastChange] [datetime] NOT NULL,
	[IdOfUserLastChange] [int] NOT NULL,
	[IsDeleted] [int] NOT NULL,
 CONSTRAINT [PK_Teams] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Users]    Script Date: 7/12/2021 2:46:56 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Users](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[UserName] [nvarchar](255) NULL,
	[Password] [nvarchar](255) NULL,
	[FirstName] [nvarchar](255) NOT NULL,
	[LastName] [nvarchar](255) NOT NULL,
	[DateOfCreation] [datetime] NOT NULL,
	[Role] [int] NOT NULL,
	[IdOfCreator] [int] NULL,
	[DateOfLastChange] [datetime] NOT NULL,
	[IdOfUserLastChange] [int] NULL,
	[IsDeleted] [int] NOT NULL,
 CONSTRAINT [PK_Users] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[UsersTeams]    Script Date: 7/12/2021 2:46:56 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[UsersTeams](
	[IdOfUser] [int] NOT NULL,
	[IdOfTeam] [int] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Work_Log]    Script Date: 7/12/2021 2:46:56 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Work_Log](
	[Id] [int] NOT NULL,
	[IdOfTask] [int] NOT NULL,
	[IdOfUser] [int] NOT NULL,
	[Time] [int] NOT NULL,
	[Date] [date] NOT NULL,
 CONSTRAINT [PK_Work_Log] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
ALTER TABLE [dbo].[Projects] ADD  CONSTRAINT [DF_Project_DateOfCreation]  DEFAULT (getdate()) FOR [DateOfCreation]
GO
ALTER TABLE [dbo].[Projects] ADD  CONSTRAINT [DF_Project_DateOfLastChange]  DEFAULT (getdate()) FOR [DateOfLastChange]
GO
ALTER TABLE [dbo].[Tasks] ADD  CONSTRAINT [DF_Task_DateOfCreation]  DEFAULT (getdate()) FOR [DateOfCreation]
GO
ALTER TABLE [dbo].[Tasks] ADD  CONSTRAINT [DF_Task_DateOfLastChange]  DEFAULT (getdate()) FOR [DateOfLastChange]
GO
ALTER TABLE [dbo].[Teams] ADD  CONSTRAINT [DF_Teams_DateOfCreation]  DEFAULT (getdate()) FOR [DateOfCreation]
GO
ALTER TABLE [dbo].[Teams] ADD  CONSTRAINT [DF_Teams_DateOfLastChange]  DEFAULT (getdate()) FOR [DateOfLastChange]
GO
ALTER TABLE [dbo].[Users] ADD  CONSTRAINT [DF_Users_DateOfCreation]  DEFAULT (getdate()) FOR [DateOfCreation]
GO
ALTER TABLE [dbo].[Users] ADD  CONSTRAINT [DF_Users_DateOfLastChange]  DEFAULT (getdate()) FOR [DateOfLastChange]
GO
ALTER TABLE [dbo].[Work_Log] ADD  CONSTRAINT [DF_Work_Log_Date]  DEFAULT (getdate()) FOR [Date]
GO
ALTER TABLE [dbo].[Projects]  WITH CHECK ADD  CONSTRAINT [FK_Project_Teams] FOREIGN KEY([IdTeam])
REFERENCES [dbo].[Teams] ([Id])
GO
ALTER TABLE [dbo].[Projects] CHECK CONSTRAINT [FK_Project_Teams]
GO
ALTER TABLE [dbo].[Projects]  WITH CHECK ADD  CONSTRAINT [FK_Project_Users_Creator] FOREIGN KEY([IdOfCreator])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Projects] CHECK CONSTRAINT [FK_Project_Users_Creator]
GO
ALTER TABLE [dbo].[Projects]  WITH CHECK ADD  CONSTRAINT [FK_Project_Users_Last_Edit] FOREIGN KEY([IdOfUserLastChange])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Projects] CHECK CONSTRAINT [FK_Project_Users_Last_Edit]
GO
ALTER TABLE [dbo].[Tasks]  WITH NOCHECK ADD  CONSTRAINT [FK_Task_Project] FOREIGN KEY([Id])
REFERENCES [dbo].[Projects] ([Id])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Task_Project]
GO
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Task_Users_Assignee] FOREIGN KEY([IdOfAssignee])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Task_Users_Assignee]
GO
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Task_Users_Creator] FOREIGN KEY([IdOfCreator])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Task_Users_Creator]
GO
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Task_Users_Last_Edit] FOREIGN KEY([IdOfTheUserLastChange])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Task_Users_Last_Edit]
GO
ALTER TABLE [dbo].[Teams]  WITH CHECK ADD  CONSTRAINT [FK_Teams_Users_Creator] FOREIGN KEY([IdOfCreator])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Teams] CHECK CONSTRAINT [FK_Teams_Users_Creator]
GO
ALTER TABLE [dbo].[Teams]  WITH CHECK ADD  CONSTRAINT [FK_Teams_Users_LastEdit] FOREIGN KEY([IdOfUserLastChange])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Teams] CHECK CONSTRAINT [FK_Teams_Users_LastEdit]
GO
ALTER TABLE [dbo].[Users]  WITH CHECK ADD  CONSTRAINT [FK_Users_Users_Creator] FOREIGN KEY([IdOfCreator])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [FK_Users_Users_Creator]
GO
ALTER TABLE [dbo].[Users]  WITH CHECK ADD  CONSTRAINT [FK_Users_Users_LastEdit] FOREIGN KEY([IdOfUserLastChange])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [FK_Users_Users_LastEdit]
GO
ALTER TABLE [dbo].[UsersTeams]  WITH CHECK ADD  CONSTRAINT [FK_UsersTeams_Teams] FOREIGN KEY([IdOfTeam])
REFERENCES [dbo].[Teams] ([Id])
GO
ALTER TABLE [dbo].[UsersTeams] CHECK CONSTRAINT [FK_UsersTeams_Teams]
GO
ALTER TABLE [dbo].[UsersTeams]  WITH CHECK ADD  CONSTRAINT [FK_UsersTeams_Users] FOREIGN KEY([IdOfUser])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[UsersTeams] CHECK CONSTRAINT [FK_UsersTeams_Users]
GO
ALTER TABLE [dbo].[Work_Log]  WITH CHECK ADD  CONSTRAINT [FK_Work_Log_Task] FOREIGN KEY([IdOfTask])
REFERENCES [dbo].[Tasks] ([Id])
GO
ALTER TABLE [dbo].[Work_Log] CHECK CONSTRAINT [FK_Work_Log_Task]
GO
ALTER TABLE [dbo].[Work_Log]  WITH CHECK ADD  CONSTRAINT [FK_Work_Log_Users] FOREIGN KEY([IdOfUser])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Work_Log] CHECK CONSTRAINT [FK_Work_Log_Users]
GO
USE [master]
GO
ALTER DATABASE [ScaleFocus-AppDB] SET  READ_WRITE 
GO
