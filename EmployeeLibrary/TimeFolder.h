﻿#ifndef TIME_FOLDER_H
#define TIME_FOLDER_H

#include <vector>

#include "TimeCard.h"
#include "../FolderLibrary/Folder.h"

class TimeFolder : public Folder
{
public:
	TimeFolder(std::string title);

	TimeFolder(const TimeFolder& src) = delete;

	TimeFolder& operator=(TimeFolder rhs) = delete;

	TimeFolder& operator=(TimeFolder&& rhs) noexcept;

	TimeFolder(TimeFolder&& src) noexcept;

	~TimeFolder() override = default;

	[[nodiscard]] std::string getTitle() const;

	[[nodiscard]] size_t size() const;

	void swap(TimeFolder& other) noexcept;
	
	void add(std::unique_ptr<Card> c) override;

	void remove() override;

	void print(std::ostream& os) const override;
	
	void write() override;

	void flip() override;

	void printCurrentCard(std::ostream& os) const;

	static std::tm getDate();

private:
	std::unique_ptr<TimeCard> current_card_;

	std::string title_;

	std::vector<std::unique_ptr<Card>> folder_;
};

#endif